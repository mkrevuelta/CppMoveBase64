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

inline void encodeFromBinToB64Txt (
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
        auto binReadSize = is.gcount ();

        if (binReadSize <= 0 || is.bad())
            return;

        encodeFromBinToB64Txt (
                     ConstSpan<char> (bin.data(),
                                      bin.data() + binReadSize),
                     Span<char> (text));

        os << text.data ();
    }
    while (os);
}

inline void decodeFromB64TxtToBin (
                std::istream & is,
                std::ostream & os,
                std::size_t numBlocks = 0)
{
    if (numBlocks == 0)
        numBlocks = 128U;

    std::vector<char> bin ((numBlocks+1) * 3U);
    std::vector<char> text (numBlocks * 4U);
    DecIntermState intermState;

    do
    {
        is.read (text.data(), text.size());
        auto textReadSize = is.gcount ();

        if ((textReadSize <= 0 && intermState.empty()) || is.bad())
            return;

        if (textReadSize < 0)
            textReadSize = 0;

        auto result = decodeFromB64TxtToBin (
                     ConstSpan<char> (text.data(),
                                      text.data() + textReadSize),
                     Span<char> (bin),
                     &intermState,
                     !is.eof());

        if (result.outcome != DecodeResult::Outcome::OkDone &&
            result.outcome != DecodeResult::Outcome::OkPartial)
            return;

        os.write (bin.data(), result.size);
    }
    while (os);
}

} // namespace cmbase64

#endif // __CPPMOVEBASE64_STREAMED_H__
