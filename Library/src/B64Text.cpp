/*
    B64Text.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64/B64Text.h>
#include <CppMoveBase64.h>

#include "Buffer.h"
#include "Errors.h"

namespace cmbase64
{

struct B64Text::Impl
{
    internal::Buffer buff;
    std::string errMessage;
};

CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL (B64Text)

Span<char> B64Text::span ()
{
    if ( ! pImpl)
        return Span<char>();

    char * begin = pImpl->buff.data.get ();

    return Span<char>(begin,
                      begin + pImpl->buff.totalSize);
}

ConstSpan<char> B64Text::span () const
{
    if ( ! pImpl)
        return ConstSpan<char>();

    const char * begin = pImpl->buff.data.get ();

    return ConstSpan<char>(begin,
                           begin + pImpl->buff.totalSize);
}

const char * B64Text::c_str () const
{
    return pImpl && pImpl->buff.data ? pImpl->buff.data.get() : "";
}

const char * B64Text::errorMessage () const
{
    switch (status)
    {
        case ErrorStatus::NoError:
            return "All OK. No error... Duh!";

        case ErrorStatus::BadAlloc:
            return "Allocation error. Not enough memory";

        case ErrorStatus::DoubleException:
            return "Double exception. Error while storing error info";

        case ErrorStatus::Exception:
            return pImpl && ! pImpl->errMessage.empty()      ?
                   pImpl->errMessage.c_str ()                :
                   "Unexpected status with no error message";

        default:
            return "Unexpected error status";
    }
}

ErrorStatus B64Text::encode (ConstSpan<char> binData) CMBASE64_NOEXCEPT
{
    std::size_t requiredSize = encodedSize (binData.size ());

    reserveAtLeast (requiredSize);

    if (status == ErrorStatus::NoError)
        cmbase64::encode (binData, span());

    return status;
}

ErrorStatus B64Text::reserveAtLeast (std::size_t capacity)
                                                      CMBASE64_NOEXCEPT
{
    status = ErrorStatus::NoError;
    
    if ( ! pImpl || pImpl->buff.totalSize < capacity)
    {
        internal::runWithErrorHarness (status, pImpl, [&]()
        {
            if ( ! pImpl)
                pImpl.allocate ();

            pImpl->buff.totalSize = capacity;
            pImpl->buff.data.reset (new char [capacity]);
        });
    }
    
    return status;
}

} // namespace cmbase64
