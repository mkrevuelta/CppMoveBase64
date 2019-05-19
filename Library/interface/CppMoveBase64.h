/*
    CppMoveBase64.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include "CppMoveBase64/B64Text.h"
#include <vector>
#include <array>
#include <string>

namespace cmbase64
{

inline B64Text encode (ConstSpan<char> binData)
{
    return B64Text::encode (binData);
}

inline B64Text encode (ConstSpan<unsigned char> binData)
{
    return B64Text::encode (
                ConstSpan<char> (
                    reinterpret_cast<const char *>(binData.cbegin()),
                    reinterpret_cast<const char *>(binData.cend())   ));
}

template <typename T, typename A>
B64Text encode (const std::vector<T,A> & binData)
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    const std::vector<must_be_fundamental_type,A> & ref = binData;
    
    const char * begin = reinterpret_cast<const char *>(ref.data());
    return B64Text::encode (
                ConstSpan<char> (
                    begin,
                    begin + (ref.size()*sizeof(T)) ));
}

template <typename T, std::size_t N>
B64Text encode (const std::array<T,N> & binData)
{
    typedef typename std::enable_if
                <std::is_fundamental<T>::value,T>::type
                    must_be_fundamental_type;

    const std::array<must_be_fundamental_type,N> & ref = binData;
    
    const char * begin = reinterpret_cast<const char *>(ref.data());
    return B64Text::encode (
                ConstSpan<char> (
                    begin,
                    begin + (N*sizeof(T)) ));
}

template <typename C, typename T, typename A>
B64Text encode (const std::basic_string<C,T,A> & binData)
{
    typedef typename std::enable_if
                <std::is_fundamental<C>::value,C>::type
                    must_be_fundamental_type;

    const std::basic_string<must_be_fundamental_type,T,A>
                & ref = binData;
    
    const char * begin = reinterpret_cast<const char *>(ref.data());
    return B64Text::encode (
                ConstSpan<char> (
                    begin,
                    begin + (ref.size()*sizeof(C)) ));
}

} // namespace cmbase64
