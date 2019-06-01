/*
    BinData.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64/BinData.h>
#include <CppMoveBase64.h>

#include "Buffer.h"
#include "Errors.h"

namespace cmbase64
{

struct BinData::Impl
{
    internal::Buffer buff;
    std::size_t size;
    std::string errMessage;
};

CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL (BinData)

Span<char> BinData::span ()
{
    if ( ! pImpl)
        return Span<char>();

    char * begin = pImpl->buff.data.get ();

    return Span<char>(begin,
                      begin + pImpl->size);
}

ConstSpan<char> BinData::span () const
{
    if ( ! pImpl)
        return ConstSpan<char>();

    const char * begin = pImpl->buff.data.get ();

    return ConstSpan<char>(begin,
                           begin + pImpl->size);
}

const char * BinData::errorMessage () const
{
    switch (status)
    {
        case ErrorStatus::Ok:
            return "All OK. No error... Duh!";

        case ErrorStatus::OkPartial:
            return "Ok. Intermediate decoding state";

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

ErrorStatus BinData::decodeFromB64Txt (ConstSpan<char> b64TxtSrc)
                                                           CMBASE64_NOEXCEPT
{
    std::size_t requiredSize = decodedMaxSize (b64TxtSrc.size ());

    reserveAtLeast (requiredSize);

    if (status != ErrorStatus::Ok)
        return status;

    char * begin = pImpl->buff.data.get ();
    std::size_t reservedSize = pImpl->buff.totalSize;

    auto result = cmbase64::decodeFromB64TxtToBin (
                            b64TxtSrc,
                            Span<char>(begin,
                                       begin + reservedSize));
    pImpl->size = result.size;

    switch (result.outcome)
    {
    case DecodeResult::Outcome::OkDone:
        status = ErrorStatus::Ok;
        break;

    case DecodeResult::Outcome::OkPartial:
        status = ErrorStatus::OkPartial;
        break;

    case DecodeResult::Outcome::DestSpanIsTooSmall:
        internal::runWithErrorHarness (status, pImpl, [&]()
        {
            throw std::runtime_error (
                "Unexpected end of buffer while decoding Base64");
        });
        break;

    case DecodeResult::Outcome::InvalidInput:
        internal::runWithErrorHarness (status, pImpl, [&]()
        {
            throw std::runtime_error (
                "Invalid input character while decoding Base64");
        });
        break;
    }

    return status;
}

ErrorStatus BinData::reserveAtLeast (std::size_t capacity)
                                                      CMBASE64_NOEXCEPT
{
    status = ErrorStatus::Ok;

    if ( ! pImpl || pImpl->buff.totalSize < capacity)
    {
        internal::runWithErrorHarness (status, pImpl, [&]()
        {
            if ( ! pImpl)
                pImpl.allocate ();

            pImpl->buff.totalSize = capacity;
            pImpl->buff.data.reset (new char [capacity]);
            pImpl->size = 0;
        });
    }

    return status;
}

} // namespace cmbase64
