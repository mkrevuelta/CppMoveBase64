/*
    CppMoveBase64/B64Text.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_B64TEXT_H__
#define __CPPMOVEBASE64_B64TEXT_H__

#include "ApiMacros.h"
#include "PImplMacros.h"
#include "Span.h"

namespace cmbase64
{

class CMBASE64_API B64Text
{
    CMBASE64_DECLARE_PIMPL (B64Text)

public:

         Span<char> span ()       throw();
    ConstSpan<char> span () const throw();

    const char * c_str () const throw();   // Returns "" if empty

    bool isOk    () const throw() { return status == ErrorStatus::Ok; }
    bool isError () const throw() { return ! isOk(); }
    const char * errorMessage () const throw();

    ErrorStatus reserveAtLeast (std::size_t capacity) throw();

    ErrorStatus encodeFromBin (ConstSpan<char> binSrc) throw();
};

CMBASE64_INLINE_SYMMETRIC_SWAP (B64Text)

} // namespace cmbase64

#endif // __CPPMOVEBASE64_B64TEXT_H__
