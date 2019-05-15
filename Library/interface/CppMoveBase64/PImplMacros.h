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

#define CMBASE64_DECLARE_PIMPL(CLASS)                     \
                                                          \
private:                                                  \
                                                          \
    struct Impl;                                          \
    UniquePtr<Impl> pImpl;                                \
                                                          \
public:                                                   \
                                                          \
    CLASS () CMBASE64_NOEXCEPT;                           \
    CLASS (CLASS &&) CMBASE64_NOEXCEPT;                   \
    CLASS (const CLASS &);                                \
    ~CLASS () CMBASE64_NOEXCEPT;                          \
    CLASS & operator= (CLASS &&) CMBASE64_NOEXCEPT;       \
    CLASS & operator= (const CLASS &);                    \
    void swap (CLASS &) CMBASE64_NOEXCEPT;

#define CMBASE64_INLINE_SYMMETRIC_SWAP(CLASS)             \
                                                          \
inline void swap (CLASS & a, CLASS & b) CMBASE64_NOEXCEPT \
{                                                         \
    a.swap (b);                                           \
}

#define CMBASE64_IMPLEMENT_INNER_PIMPL(FULLNAME,CLASS)    \
                                                          \
FULLNAME::CLASS () CMBASE64_NOEXCEPT                      \
{                                                         \
}                                                         \
                                                          \
FULLNAME::CLASS (FULLNAME && other) CMBASE64_NOEXCEPT     \
    :                                                     \
    pImpl(std::move(other.pImpl))                         \
{                                                         \
}                                                         \
                                                          \
FULLNAME::CLASS (const FULLNAME & other)                  \
    :                                                     \
    pImpl(other.pImpl ? *other.pImpl.get()                \
                      : Impl())                           \
{                                                         \
}                                                         \
                                                          \
FULLNAME::~CLASS () CMBASE64_NOEXCEPT                     \
{                                                         \
}                                                         \
                                                          \
FULLNAME & FULLNAME::operator= (                          \
                FULLNAME && other) CMBASE64_NOEXCEPT      \
{                                                         \
    pImpl = std::move (other.pImpl);                      \
    return *this;                                         \
}                                                         \
                                                          \
FULLNAME & FULLNAME::operator= (                          \
                const FULLNAME & other)                   \
{                                                         \
    FULLNAME tmp(other);                                  \
    swap (tmp);                                           \
    return *this;                                         \
}                                                         \
                                                          \
void FULLNAME::swap (FULLNAME & other) CMBASE64_NOEXCEPT  \
{                                                         \
    pImpl.swap (other.pImpl);                             \
}

#define CMBASE64_IMPLEMENT_PIMPL(CLASS)                   \
        CMBASE64_IMPLEMENT_INNER_PIMPL (CLASS, CLASS)

#endif // __CPPMOVEBASE64_PIMPLMACROS_H__

