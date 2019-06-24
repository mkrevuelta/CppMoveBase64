/*
    CppMoveBase64/PImplMacros.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_PIMPLMACROS_H__
#define __CPPMOVEBASE64_PIMPLMACROS_H__

#include "ApiMacros.h"
#include "UniquePtr.h"
#include "ErrorStatus.h"

// ------------------------------------------------------------ //

#define CMBASE64_DECLARE_PIMPL(CLASS)                            \
                                                                 \
private:                                                         \
                                                                 \
    struct Impl;                                                 \
    UniquePtr<Impl> pImpl;                                       \
                                                                 \
    ErrorStatus status;                                          \
                                                                 \
public:                                                          \
                                                                 \
    CLASS () throw();                                            \
    CLASS (CLASS &&) throw();                                    \
    ~CLASS () throw();                                           \
    CLASS & operator= (CLASS &&) throw();                        \
    void swap (CLASS &) throw();

// ------------------------------------------------------------ //

#define CMBASE64_INLINE_SYMMETRIC_SWAP(CLASS)                    \
                                                                 \
inline void swap (CLASS & a, CLASS & b) throw()                  \
{                                                                \
    a.swap (b);                                                  \
}

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_INNER_PIMPL(FULLNAME,CLASS)           \
                                                                 \
FULLNAME::CLASS () throw()                                       \
    :                                                            \
    status(ErrorStatus::Ok)                                      \
{                                                                \
}                                                                \
                                                                 \
FULLNAME::CLASS (FULLNAME && other) throw()                      \
    :                                                            \
    pImpl(std::move(other.pImpl)),                               \
    status(other.status)                                         \
{                                                                \
    other.status = ErrorStatus::Ok;                              \
}                                                                \
                                                                 \
                                                                 \
FULLNAME::~CLASS () throw()                                      \
{                                                                \
}                                                                \
                                                                 \
FULLNAME & FULLNAME::operator= (                                 \
                FULLNAME && other) throw()                       \
{                                                                \
    pImpl = std::move (other.pImpl);                             \
    status = other.status;                                       \
    other.status = ErrorStatus::Ok;                              \
    return *this;                                                \
}                                                                \
                                                                 \
void FULLNAME::swap (FULLNAME & other) throw()                   \
{                                                                \
    pImpl.swap (other.pImpl);                                    \
                                                                 \
    ErrorStatus tmp = status;                                    \
    status = other.status;                                       \
    other.status = tmp;                                          \
}

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_PIMPL(CLASS)                          \
        CMBASE64_IMPLEMENT_INNER_PIMPL (CLASS, CLASS)

// ------------------------------------------------------------ //

#endif // __CPPMOVEBASE64_PIMPLMACROS_H__

