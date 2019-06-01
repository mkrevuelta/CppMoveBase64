/*
    CppMoveBase64.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include "CppMoveBase64/B64Text.h"
#include "CppMoveBase64/BinData.h"
#include "CppMoveBase64/DecIntermState.h"
#include <stdexcept>

namespace cmbase64
{

inline std::size_t encodedSize (std::size_t binSrcSizeInBytes)
                                                CMBASE64_NOEXCEPT
{
    return (binSrcSizeInBytes+2U)/3U*4U + 1U;
}

inline std::size_t decodedMaxSize (std::size_t b64TextSrcSizeInChars)
                                                CMBASE64_NOEXCEPT
{
    return (b64TextSrcSizeInChars+3U)/4U*3U;
}

inline B64Text encodeFromBin (ConstSpan<char> binSrc)
{
    B64Text result;

    result.encodeFromBin (binSrc);

    if (result.isError())
        throw std::runtime_error (result.errorMessage());

    return result;
}

template <typename T>
B64Text encodeFromBin (ConstSpan<T> binSrc)
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    ConstSpan<must_be_fundamental_type> & ref = binSrc;

    return encodeFromBin (
                ConstSpan<char> (
                    reinterpret_cast<const char *>(ref.cbegin()),
                    reinterpret_cast<const char *>(ref.cend())   ));
}

CMBASE64_API void encodeFromBinToB64Txt (
                    ConstSpan<char> binSrc,
                    Span<char> textDest)
                            CMBASE64_NOEXCEPT;

template <typename T>
void encodeFromBinToB64Txt (
        ConstSpan<T> binSrc,
        Span<char> textDest)
                CMBASE64_NOEXCEPT
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    ConstSpan<must_be_fundamental_type> & ref = binSrc;

    encodeFromBinToB64Txt (
            ConstSpan<char> (
                    reinterpret_cast<const char *>(ref.cbegin()),
                    reinterpret_cast<const char *>(ref.cend())   ),
            textDest);
}

struct DecodeResult
{
    enum class Outcome
    {
        OkDone, OkPartial, DestSpanIsTooSmall, InvalidInput
    };

    std::size_t size;
    Outcome outcome;
};

CMBASE64_API DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<char> binDest,
                    DecIntermState * intermState = nullptr,
                    bool toBeContinued = false)
                            CMBASE64_NOEXCEPT;

//-- template overloads...

} // namespace cmbase64
