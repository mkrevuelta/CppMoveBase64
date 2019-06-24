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

CMBASE64_IMPLEMENT_PIMPL (BinData)

Span<char> BinData::span () throw()
{
    if ( ! pImpl)
        return Span<char>();

    char * begin = pImpl->buff.data.get ();

    return Span<char>(begin,
                      begin + pImpl->size);
}

ConstSpan<char> BinData::span () const throw()
{
    if ( ! pImpl)
        return ConstSpan<char>();

    const char * begin = pImpl->buff.data.get ();

    return ConstSpan<char>(begin,
                           begin + pImpl->size);
}

const char * BinData::errorMessage () const throw()
{
    return internal::errorMessage (
                        status,
                        pImpl ? &pImpl->errMessage : nullptr);
}

ErrorStatus BinData::decodeFromB64Txt (ConstSpan<char> b64TxtSrc) throw()
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
        status = internal::runWithErrorHarness (pImpl, [&]()
        {
            throw std::runtime_error (
                "Unexpected end of buffer while decoding Base64");
        });
        break;

    case DecodeResult::Outcome::InvalidInput:
        status = internal::runWithErrorHarness (pImpl, [&]()
        {
            throw std::runtime_error (
                "Invalid input character while decoding Base64");
        });
        break;
    }

    return status;
}

ErrorStatus BinData::reserveAtLeast (std::size_t capacity) throw()
{
    status = ErrorStatus::Ok;

    if ( ! pImpl || pImpl->buff.totalSize < capacity)
    {
        status = internal::runWithErrorHarness (pImpl, [&]()
        {
            if ( ! pImpl)
                pImpl.allocate ();

            pImpl->buff.data.reset (new char [capacity]);
            pImpl->buff.totalSize = capacity;
            pImpl->size = 0;
        });
    }

    return status;
}

} // namespace cmbase64
