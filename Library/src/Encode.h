/*
    Encode.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_ENCODE_H__
#define __CPPMOVEBASE64_ENCODE_H__

#include <CppMoveBase64/ApiMacros.h>

#ifndef COMPILING_CMBASE64
#error "This .h should never be included from out of the CppMoveBase64 project"
#endif

#include <CppMoveBase64/Span.h>
#include "Buffer.h"

namespace cmbase64
{

namespace internal
{

Buffer encode (ConstSpan<char> binData);

} // namespace internal

} // namespace cmbase64


#endif // __CPPMOVEBASE64_ENCODE_H__
