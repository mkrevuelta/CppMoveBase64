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

#define CMBASE64_DECLARE_MOVE_ONLY_PIMPL(CLASS)                  \
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
    CLASS () CMBASE64_NOEXCEPT;                                  \
    CLASS (CLASS &&) CMBASE64_NOEXCEPT;                          \
    ~CLASS () CMBASE64_NOEXCEPT;                                 \
    CLASS & operator= (CLASS &&) CMBASE64_NOEXCEPT;              \
    void swap (CLASS &) CMBASE64_NOEXCEPT;

// ------------------------------------------------------------ //

#define CMBASE64_DECLARE_COPYABLE_PIMPL(CLASS)                   \
                                                                 \
    CMBASE64_DECLARE_MOVE_ONLY_PIMPL (CLASS)                     \
                                                                 \
public:                                                          \
                                                                 \
    CLASS (const CLASS &);                                       \
    CLASS & operator= (const CLASS &);

// ------------------------------------------------------------ //

#define CMBASE64_INLINE_SYMMETRIC_SWAP(CLASS)                    \
                                                                 \
inline void swap (CLASS & a, CLASS & b) CMBASE64_NOEXCEPT        \
{                                                                \
    a.swap (b);                                                  \
}

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_INNER_MOVE_ONLY_PIMPL(FULLNAME,CLASS) \
                                                                 \
FULLNAME::CLASS () CMBASE64_NOEXCEPT                             \
    :                                                            \
    status(ErrorStatus::NoError)                                 \
{                                                                \
}                                                                \
                                                                 \
FULLNAME::CLASS (FULLNAME && other) CMBASE64_NOEXCEPT            \
    :                                                            \
    pImpl(std::move(other.pImpl)),                               \
    status(other.status)                                         \
{                                                                \
    other.status = ErrorStatus::NoError;                         \
}                                                                \
                                                                 \
                                                                 \
FULLNAME::~CLASS () CMBASE64_NOEXCEPT                            \
{                                                                \
}                                                                \
                                                                 \
FULLNAME & FULLNAME::operator= (                                 \
                FULLNAME && other) CMBASE64_NOEXCEPT             \
{                                                                \
    pImpl = std::move (other.pImpl);                             \
    status = other.status;                                       \
    other.status = ErrorStatus::NoError;                         \
    return *this;                                                \
}                                                                \
                                                                 \
void FULLNAME::swap (FULLNAME & other) CMBASE64_NOEXCEPT         \
{                                                                \
    pImpl.swap (other.pImpl);                                    \
                                                                 \
    ErrorStatus tmp = status;                                    \
    status = other.status;                                       \
    other.status = tmp;                                          \
}

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_INNER_COPYABLE_PIMPL(FULLNAME,CLASS)  \
                                                                 \
    CMBASE64_IMPLEMENT_INNER_MOVE_ONLY_PIMPL(FULLNAME,CLASS)     \
                                                                 \
FULLNAME::CLASS (const FULLNAME & other)                         \
    :                                                            \
    pImpl(other.pImpl ? *other.pImpl.get()                       \
                      : Impl()),                                 \
    status(other.status)                                         \
{                                                                \
}                                                                \
                                                                 \
FULLNAME & FULLNAME::operator= (                                 \
                const FULLNAME & other)                          \
{                                                                \
    FULLNAME tmp(other);                                         \
    swap (tmp);                                                  \
    return *this;                                                \
}

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL(CLASS)                \
        CMBASE64_IMPLEMENT_INNER_MOVE_ONLY_PIMPL (CLASS, CLASS)

// ------------------------------------------------------------ //

#define CMBASE64_IMPLEMENT_COPYABLE_PIMPL(CLASS)                 \
        CMBASE64_IMPLEMENT_INNER_COPYABLE_PIMPL (CLASS, CLASS)

// ------------------------------------------------------------ //

#endif // __CPPMOVEBASE64_PIMPLMACROS_H__

