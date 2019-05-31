/*
    Errors.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_ERRORS_H__
#define __CPPMOVEBASE64_ERRORS_H__

#include <CppMoveBase64/ApiMacros.h>
#include <CppMoveBase64/ErrorStatus.h>
#include <CppMoveBase64/UniquePtr.h>

#include <new>
#include <functional>
#include <string>

#ifndef COMPILING_CMBASE64
#error "This .h should never be included from out of the CppMoveBase64 project"
#endif

namespace cmbase64
{

namespace internal
{

template <typename I>
void runWithErrorHarness (
                    ErrorStatus & status,
                    UniquePtr<I> & pImpl,
                    std::function<void(void)> task)
{
    try
    {
        status = ErrorStatus::Ok;

        task ();
    }
    catch (const std::bad_alloc &)
    {
        status = ErrorStatus::BadAlloc;
    }
    catch (const std::exception & ex)
    {
        status = ErrorStatus::Exception;

        try
        {
            if (pImpl)
                pImpl->errMessage = ex.what ();
            return;
        }
        catch (...)
        {
            status = ErrorStatus::DoubleException;
        }
    }
}

} // namespace internal

} // namespace cmbase64

#endif // __CPPMOVEBASE64_ERRORS_H__
