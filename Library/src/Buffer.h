/*
    Buffer.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_BUFFER_H__
#define __CPPMOVEBASE64_BUFFER_H__

#include <CppMoveBase64/ApiMacros.h>

#ifndef COMPILING_CMBASE64
#error "This .h should never be included from out of the CppMoveBase64 project"
#endif

#include <memory>

namespace cmbase64
{

namespace internal
{

struct Buffer
{
    struct Deleter
    {
        void operator() (char * p)
        {
            delete [] p;
        }
    };

    std::unique_ptr<char,Deleter>  data;
    std::size_t                    totalSize;
};

} // namespace internal

} // namespace cmbase64

#endif // __CPPMOVEBASE64_BUFFER_H__
