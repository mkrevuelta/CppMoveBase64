/*
    CppMoveBase64/UniquePtr.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_UNIQUEPTR_H__
#define __CPPMOVEBASE64_UNIQUEPTR_H__

#include "ApiMacros.h"

#include <utility>

namespace cmbase64
{

template <typename T>
class CMBASE64_API UniquePtr
{
private:

    T * ptr;

    UniquePtr<T> & operator= (const UniquePtr<T> &) { throw 0; } // disable
    UniquePtr (T * p) CMBASE64_NOEXCEPT : ptr(p) {}

public:

    UniquePtr ();
    explicit UniquePtr (const T &);
    ~UniquePtr () CMBASE64_NOEXCEPT;

    UniquePtr<T> & operator= (UniquePtr<T> && other) CMBASE64_NOEXCEPT
    {
        UniquePtr<T> tmp (std::move(other));
        swap (tmp);
        return *this;
    }

    UniquePtr (UniquePtr<T> && other) CMBASE64_NOEXCEPT
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    void swap (UniquePtr<T> & other) CMBASE64_NOEXCEPT
    {
        T * tmp = ptr;
        ptr = other.ptr;
        other.ptr = tmp;
    }

    bool    empty () const { return ptr == nullptr; }
    operator bool () const { return ptr != nullptr; }

    const T * get        () const { return  ptr; }
          T * get        ()       { return  ptr; }
    const T * operator-> () const { return  ptr; }
          T * operator-> ()       { return  ptr; }
    const T & operator*  () const { return *ptr; }
          T & operator*  ()       { return *ptr; }
};

template <typename T>
void swap (UniquePtr<T> & a, UniquePtr<T> & b)
{
    a.swap (b);
}

#ifdef COMPILING_CMBASE64

template <typename T>
UniquePtr<T>::UniquePtr ()
    :
    ptr (new T)
{
}

template <typename T>
UniquePtr<T>::UniquePtr (const T & t)
    :
    ptr (new T(t))
{
}

template <typename T>
UniquePtr<T>::~UniquePtr () CMBASE64_NOEXCEPT
{
    if (ptr)
        delete ptr;
}

#endif // COMPILING_CMBASE64

} // namespace cmbase64

#endif // __CPPMOVEBASE64_UNIQUEPTR_H__

