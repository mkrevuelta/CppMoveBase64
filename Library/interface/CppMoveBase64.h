/*
    CppMoveBase64.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include "CppMoveBase64/B64Text.h"
#include <vector>

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

template <typename T>
B64Text encode (const std::vector<T> & binData)
{
    const char * begin = reinterpret_cast<const char *>(binData.data());
    return B64Text::encode (
                ConstSpan<char> (
                    begin,
                    begin + (binData.size()*sizeof(T)) ));
}

} // namespace cmbase64
