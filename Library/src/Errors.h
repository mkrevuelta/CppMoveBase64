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
ErrorStatus runWithErrorHarness (
                    UniquePtr<I> & pImpl,
                    std::function<void(void)> task)
{
    try
    {
        task ();

        return ErrorStatus::Ok;
    }
    catch (const std::bad_alloc &)
    {
        return ErrorStatus::BadAlloc;
    }
    catch (const std::exception & ex)
    {
        try
        {
            if (pImpl)
                pImpl->errMessage = ex.what ();

            return ErrorStatus::Exception;
        }
        catch (...)
        {
            return ErrorStatus::DoubleException;
        }
    }
}

inline
const char * errorMessage (
                    ErrorStatus status,
                    const std::string * errMessage)
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
            return errMessage && ! errMessage->empty() ?
                   errMessage->c_str ()                 :
                   "Unexpected status with no error message";

        default:
            return "Unexpected error status";
    }
}

} // namespace internal

} // namespace cmbase64

#endif // __CPPMOVEBASE64_ERRORS_H__
