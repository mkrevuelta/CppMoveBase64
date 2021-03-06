/*
    CppMoveBase64/ErrorStatus.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_ERRORSTATUS_H__
#define __CPPMOVEBASE64_ERRORSTATUS_H__

#include "ApiMacros.h"
#include <cstdint>

namespace cmbase64
{

enum class ErrorStatus : intptr_t
{
    Ok, OkPartial, Exception, BadAlloc, DoubleException
};

} // namespace cmbase64

#endif // __CPPMOVEBASE64_ERRORSTATUS_H__
