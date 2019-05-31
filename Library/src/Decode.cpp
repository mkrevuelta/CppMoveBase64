/*
    Decode.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64.h>
#include <CppMoveBase64/ErrorStatus.h>

namespace cmbase64
{

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

//-- additional parameter for intermediate decoding bytes
//-- additional parameter to indicate what to do if input ends in the middle of a pack without '=' (a "to be continued" flag)
CMBASE64_API DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<char> binDest)
                            CMBASE64_NOEXCEPT
{
    DecodeResult result;

    unsigned char unpacked[4];
    unsigned unpackedCount = 0;

    //-- If a previous state is received, copy to unpacked and update unpackedCount accordingly

//--    std::size_t destCapacity = binDest.size ();

//--    const char * src = textSrc.begin ();
//--    auto dst = reinterpret_cast<unsigned char *> (
//--                                        binDest.begin ());

    for (char b64char : textSrc)
    {
        if (b64char == '\0')
            break;

        unsigned char value = table[static_cast<unsigned char>(b64char)];

        if (value == space || value == na)  //-- Skip invalid input characters. TODO: return error, maybe?
            continue;

        if (value == equal)
            break;

        unpacked[unpackedCount++] = value;

        if (unpackedCount < 4)
            continue;

        //-- Pack the bits in 3 bytes and store them in destination buffer (if they fit!)
    }

    //-- if (unpackedCount > 0)
    //--     Pack the bits in 1 or 2 bytes and store them in destination buffer (if they fit!)
    //--     Or put them in the intermediate state if they don't fit in the output

    //--
    result.size = 0;
    result.outcome = DecodeResult::Outcome::OkPartial;

    return result;
}

} // namespace cmbase64
