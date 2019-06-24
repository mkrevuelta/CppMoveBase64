/*
    CppMoveBase64/BinData.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_BINDATA_H__
#define __CPPMOVEBASE64_BINDATA_H__

#include "ApiMacros.h"
#include "PImplMacros.h"
#include "Span.h"

namespace cmbase64
{

class CMBASE64_API BinData
{
    CMBASE64_DECLARE_PIMPL (BinData)

public:

         Span<char> span ()       throw();
    ConstSpan<char> span () const throw();

    bool isFinishedOk () const { return status == ErrorStatus::Ok; }

    bool isOk    () const { return status == ErrorStatus::Ok ||
                                   status == ErrorStatus::OkPartial; }
    bool isError () const { return ! isOk(); }
    const char * errorMessage () const;

    ErrorStatus reserveAtLeast (std::size_t capacity) throw();

    ErrorStatus decodeFromB64Txt (ConstSpan<char> b64Text) throw();
};

CMBASE64_INLINE_SYMMETRIC_SWAP (BinData)

} // namespace cmbase64

#endif // __CPPMOVEBASE64_BINDATA_H__
