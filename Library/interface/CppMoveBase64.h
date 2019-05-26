/*
    CppMoveBase64.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include "CppMoveBase64/B64Text.h"
#include <stdexcept>

namespace cmbase64
{

inline std::size_t encodedSize (std::size_t binBytes)
                                                CMBASE64_NOEXCEPT
{
    return (binBytes+2U)/3U*4U + 1U;
}

inline B64Text encode (ConstSpan<char> binData)
{
    B64Text result;
    
    result.encode (binData);

    if (result.isError())
        throw std::runtime_error (result.errorMessage());

    return result;
}

template <typename T>
B64Text encode (ConstSpan<T> binData)
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    ConstSpan<must_be_fundamental_type> & ref = binData;

    return encode (
                ConstSpan<char> (
                    reinterpret_cast<const char *>(ref.cbegin()),
                    reinterpret_cast<const char *>(ref.cend())   ));
}

CMBASE64_API void encode (
                    ConstSpan<char> binSrc,
                    Span<char> textDest)
                            CMBASE64_NOEXCEPT;

template <typename T>
void encode (
        ConstSpan<T> binData,
        Span<char> text)
                CMBASE64_NOEXCEPT
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    ConstSpan<must_be_fundamental_type> & ref = binData;

    encode (ConstSpan<char> (
                    reinterpret_cast<const char *>(ref.cbegin()),
                    reinterpret_cast<const char *>(ref.cend())   ));
}

} // namespace cmbase64
