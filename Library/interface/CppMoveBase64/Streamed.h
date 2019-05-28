/*
    CppMoveBase64/Streamed.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_STREAMED_H__
#define __CPPMOVEBASE64_STREAMED_H__

#include "ApiMacros.h"
#include "../CppMoveBase64.h"

#include <iostream>
#include <vector>

namespace cmbase64
{

inline void encode (
                std::istream & is,
                std::ostream & os,
                std::size_t numBlocks = 0)
{
    if (numBlocks == 0)
        numBlocks = 128U;

    std::vector<char> bin (numBlocks * 3U);
    std::vector<char> text (numBlocks * 4U + 1U);

    do
    {
        is.read (bin.data(), bin.size());
        std::size_t binReadSize = is.gcount ();

        if (binReadSize == 0 || is.bad())
            return;

        encode (ConstSpan<char> (bin.data(),
                                 bin.data() + binReadSize),
                     Span<char> (text));

        os << text.data ();
    }
    while (os);
}

} // namespace cmbase64

#endif // __CPPMOVEBASE64_STREAMED_H__
