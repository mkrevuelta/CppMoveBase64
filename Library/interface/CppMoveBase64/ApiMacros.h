/*
    CppMoveBase64/ApiMacros.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_API_MACROS_H__
#define __CPPMOVEBASE64_API_MACROS_H__

#if defined (_WIN32)
  #if defined (COMPILING_CMBASE64)
    #define CMBASE64_API __declspec(dllexport)
    #define EXTERN_TO_ALL_BUT_CMBASE64
  #else
    #define CMBASE64_API __declspec(dllimport)
    #define EXTERN_TO_ALL_BUT_CMBASE64 extern
  #endif
#elif defined (__GNUC__)
  #if __GNUC__ >= 4
    #define CMBASE64_API __attribute__ ((visibility ("default")))
  #else
    #define CMBASE64_API
  #endif
  #define EXTERN_TO_ALL_BUT_CMBASE64 extern
#else
  #define CMBASE64_API
  #define EXTERN_TO_ALL_BUT_CMBASE64 extern
  #pragma error "Missing specification of import/export method"
#endif

#define CMBASE64_NOEXCEPT throw()

#endif // __CPPMOVEBASE64_API_MACROS_H__

