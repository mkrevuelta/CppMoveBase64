/*
    Decode.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64.h>
#include <CppMoveBase64/ErrorStatus.h>
#include <CppMoveBase64/DecIntermState.h>

namespace cmbase64
{

namespace internal
{

class DecIntermStateAccessor
{
public:
    static void setPending (
                    DecIntermState & intermState,
                    ConstSpan<unsigned char> bytes)
    {
        intermState.setPending (bytes);
    }

    static ConstSpan<unsigned char> getPending (
                    const DecIntermState & intermState)
    {
        return intermState.getPending ();
    }

    static void clear (DecIntermState & intermState)
    {
        intermState.clear ();
    }
};

} // namespace internal

namespace
{

const unsigned char equal =  64;
const unsigned char space =  65;
const unsigned char    na = 255;

const unsigned char table[256] =
{
       na,    na,    na,    na,    na,    na,    na,    na,
       na, space, space, space, space, space,    na,    na, // Tab, new line..
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
    space,    na,    na,    na,    na,    na,    na,    na, // Space
       na,    na,    na,    62,    na,    na,    na,    63, // '+', '/'
       52,    53,    54,    55,    56,    57,    58,    59, // '0'..
       60,    61,    na,    na,    na, equal,    na,    na, //    ..'9', '='
       na,     0,     1,     2,     3,     4,     5,     6, // 'A'..
        7,     8,     9,    10,    11,    12,    13,    14, //     .
       15,    16,    17,    18,    19,    20,    21,    22, //     .
       23,    24,    25,    na,    na,    na,    na,    na, //     ..'Z'
       na,    26,    27,    28,    29,    30,    31,    32, // 'a'..
       33,    34,    35,    36,    37,    38,    39,    40, //     .
       41,    42,    43,    44,    45,    46,    47,    48, //     .
       49,    50,    51,    na,    na,    na,    na,    na, //     ..'z'
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na,
       na,    na,    na,    na,    na,    na,    na,    na
};

} // anonymous namespace

CMBASE64_API DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<char> binDest,
                    DecIntermState * intermState,
                    bool toBeContinued)
                            CMBASE64_NOEXCEPT
{
    DecodeResult result;

    unsigned char unpacked[4];
    unsigned unpackedCount = 0;
    bool endingMarkFound = false;

    if (intermState && ! intermState->empty())
    {
        auto pending = internal::DecIntermStateAccessor::
                            getPending (*intermState);

        for (unsigned char c : pending)
            unpacked[unpackedCount++] = c;
    }

    auto dst = reinterpret_cast<unsigned char *> (
                                        binDest.begin ());
    std::size_t dstRoom = binDest.size();

    for (char b64char : textSrc)
    {
        if (b64char == '\0')
            break;

        unsigned char value = table[static_cast<unsigned char>(b64char)];

        if (value == space)
            continue;

        if (value == na)
        {
            result.size = 0;
            result.outcome = DecodeResult::Outcome::InvalidInput;
            return result;
        }

        if (value == equal)
        {
            endingMarkFound = true;
            break;
        }

        unpacked[unpackedCount++] = value;

        if (unpackedCount < 4)
            continue;

        if (dstRoom < 3)
            break;

        dst[0] = (unpacked[0] << 2) | (unpacked[1] >> 4);
        dst[1] = (unpacked[1] << 4) | (unpacked[2] >> 2);
        dst[2] = (unpacked[2] << 6) |  unpacked[3];

        dst += 3;
        dstRoom -= 3;
        unpackedCount = 0;
    }

    if (unpackedCount > 0 &&
        (endingMarkFound || !toBeContinued || !intermState))
    {
        if (dstRoom < unpackedCount-1)
        {
            result.size = 0;
            result.outcome = DecodeResult::Outcome::DestSpanIsTooSmall;
            return result;
        }

        if (unpackedCount < 2)
        {
            result.size = 0;
            result.outcome = DecodeResult::Outcome::InvalidInput;
            return result;
        }

        dst[0] = (unpacked[0] << 2) | (unpacked[1] >> 4);

        if (unpackedCount > 2)
            dst[1] = (unpacked[1] << 4) | (unpacked[2] >> 2);

        dst += unpackedCount - 1;
        dstRoom -= unpackedCount - 1;
        unpackedCount = 0;
    }

    if (unpackedCount > 0)
    {
        internal::DecIntermStateAccessor::setPending (
                *intermState,
                ConstSpan<unsigned char> (
                        unpacked,
                        unpacked + unpackedCount));
                
        result.outcome = DecodeResult::Outcome::OkPartial;
    }
    else
    {
        if (intermState)
            internal::DecIntermStateAccessor::clear (*intermState);

        result.outcome = DecodeResult::Outcome::OkDone;
    }

    result.size = binDest.size() - dstRoom;

    return result;
}

} // namespace cmbase64
