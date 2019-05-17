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
    CMBASE64_DECLARE_MOVE_ONLY_PIMPL (B64Text)

public:

          char * data ();        // These return nullptr
    const char * data () const;  // if empty

    const char * c_str () const; // Returns "" if empty

    std::size_t size () const;   // Not including final '\0'

    bool isOk () const;
    bool isError () const  { return ! isOk(); }
    const char * errorMessage () const;

    static B64Text encode (ConstSpan<char> binData);
};

CMBASE64_INLINE_SYMMETRIC_SWAP (B64Text)

} // namespace cmbase64

#endif // __CPPMOVEBASE64_B64TEXT_H__
