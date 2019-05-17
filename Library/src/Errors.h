/*
    Errors.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_ERRORS_H__
#define __CPPMOVEBASE64_ERRORS_H__

#include <CppMoveBase64/ApiMacros.h>

#include <new>
#include <functional>

#ifndef COMPILING_CMBASE64
#error "This .h should never be included from out of the CppMoveBase64 project"
#endif

namespace cmbase64
{

namespace internal
{

struct ErrInfo
{
    std::string message;
    const char * what;
};

inline void runWithErrorHarness (
                    ErrInfo & errInfo,
                    std::function<void(void)> task)
{
    try
    {
        task ();

        errInfo.what = nullptr;
    }
    catch (const std::bad_alloc &)
    {
        errInfo.what = "Not enough memory";
    }
    catch (const std::exception & ex)
    {
        try
        {
            errInfo.message = ex.what ();

            errInfo.what = errInfo.message.c_str ();
        }
        catch (...)
        {
            errInfo.what = "Double exception";
        }
    }
}

} // namespace internal

} // namespace cmbase64

#endif // __CPPMOVEBASE64_ERRORS_H__
