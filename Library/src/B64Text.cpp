/*
    B64Text.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64/B64Text.h>

#include "Buffer.h"
#include "Encode.h"

namespace cmbase64
{

struct B64Text::Impl
{
    internal::Buffer buff;

    //-- TODO: Add members to store error information
};

CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL (B64Text)

char * B64Text::data ()
{
    return pImpl ? pImpl->buff.data.get () : nullptr;
}

const char * B64Text::data () const
{
    return pImpl ? pImpl->buff.data.get () : nullptr;
}

const char * B64Text::c_str () const
{
    return pImpl && pImpl->buff.data ? pImpl->buff.data.get() : "";
}

std::size_t B64Text::size () const // Discounts trailing '\0'
{
    return pImpl && pImpl->buff.data && pImpl->buff.totalSize>0 ?
                                        pImpl->buff.totalSize-1 : 0;
}

B64Text CMBASE64_API B64Text::encode (ConstSpan<char> binData)
{
    B64Text result;

    try
    {
        result.pImpl->buff = internal::encode (binData);
    }
    catch (...)
    {
        //-- TODO: Store error data in result, somehow
    }

    return result;
}

} // namespace cmbase64
