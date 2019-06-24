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

inline std::size_t encodedSize (std::size_t binSrcSizeInBytes) throw()
{
    return (binSrcSizeInBytes+2U)/3U*4U + 1U;
}

inline std::size_t decodedMaxSize (std::size_t b64TextSrcSizeInChars) throw()
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
                            throw();

template <typename T>
void encodeFromBinToB64Txt (
        ConstSpan<T> binSrc,
        Span<char> textDest)
                throw()
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

inline BinData decodeFromB64Txt (ConstSpan<char> b64TxtSrc)
{
    BinData result;

    result.decodeFromB64Txt (b64TxtSrc);

    if (result.isError())
        throw std::runtime_error (result.errorMessage());

    return result;
}

struct DecodeResult
{
    enum class Outcome : intptr_t
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
                            throw();

inline DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<unsigned char> binDest,
                    DecIntermState * intermState = nullptr,
                    bool toBeContinued = false)
                            throw()
{
    return decodeFromB64TxtToBin (
            textSrc,
            Span<char> (
                    reinterpret_cast<char *>(binDest.begin()),
                    reinterpret_cast<char *>(binDest.end())   ),
            intermState,
            toBeContinued);
}

template <typename T>
DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<T> binDest)
                            throw()
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    Span<must_be_fundamental_type> & ref = binDest;

    return decodeFromB64TxtToBin (
            textSrc,
            Span<char> (
                    reinterpret_cast<char *>(binDest.begin()),
                    reinterpret_cast<char *>(binDest.end())   ),
            nullptr,
            false);
}

} // namespace cmbase64
