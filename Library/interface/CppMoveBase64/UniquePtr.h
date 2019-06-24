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

public:

    UniquePtr () throw() : ptr(nullptr) {}
    ~UniquePtr () throw();

    void allocate ();

    UniquePtr<T> & operator= (UniquePtr<T> && other) throw()
    {
        UniquePtr<T> tmp (std::move(other));
        swap (tmp);
        return *this;
    }

    UniquePtr (UniquePtr<T> && other) throw()
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    void swap (UniquePtr<T> & other) throw()
    {
        T * tmp = ptr;
        ptr = other.ptr;
        other.ptr = tmp;
    }

    bool    empty () const throw() { return ptr == nullptr; }
    operator bool () const throw() { return ptr != nullptr; }

    const T * get        () const throw() { return  ptr; }
          T * get        ()       throw() { return  ptr; }
    const T * operator-> () const throw() { return  ptr; }
          T * operator-> ()       throw() { return  ptr; }
    const T & operator*  () const throw() { return *ptr; }
          T & operator*  ()       throw() { return *ptr; }
};

template <typename T>
void swap (UniquePtr<T> & a, UniquePtr<T> & b) throw()
{
    a.swap (b);
}

#ifdef COMPILING_CMBASE64

template <typename T>
void UniquePtr<T>::allocate ()
{
    T * tmp = new T;

    if (ptr)
        delete ptr;

    ptr = tmp;
}

template <typename T>
UniquePtr<T>::~UniquePtr () throw()
{
    if (ptr)
        delete ptr;
}

#endif // COMPILING_CMBASE64

} // namespace cmbase64

#endif // __CPPMOVEBASE64_UNIQUEPTR_H__

