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

         Span<char> span ();
    ConstSpan<char> span () const;

    const char * c_str () const;   // Returns "" if empty

    bool isOk    () const { return status == ErrorStatus::Ok; }
    bool isError () const { return ! isOk(); }
    const char * errorMessage () const;

    ErrorStatus reserveAtLeast (std::size_t capacity) CMBASE64_NOEXCEPT;

    ErrorStatus encodeFromBin (ConstSpan<char> binSrc) CMBASE64_NOEXCEPT;
};

CMBASE64_INLINE_SYMMETRIC_SWAP (B64Text)

} // namespace cmbase64

#endif // __CPPMOVEBASE64_B64TEXT_H__
