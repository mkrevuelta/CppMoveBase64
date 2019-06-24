/*
    CppMoveBase64/Span.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_SPAN_H__
#define __CPPMOVEBASE64_SPAN_H__

#include "ApiMacros.h"

#include <cstddef>

namespace cmbase64
{

template <typename T>
class Span
{
private:

    T * first;
    T * afterLast;

    Span<T> & operator= (const Span<T> &) { throw 0; } // disable

public:

    Span () throw()
        :
        first(nullptr),
        afterLast(nullptr)
    {}

    Span (T * from, T * afterTo) throw()
        :
        first(from),
        afterLast(afterTo)
    {}

    template <class C>
    explicit Span (C & c) throw()
        :
        first(c.data()),
        afterLast(first+c.size())
    {}

    typedef T * iterator;
    typedef const T * const_iterator;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    const T * data () const throw() { return first; }
          T * data ()       throw() { return first; }

    std::ptrdiff_t ssize () const throw()
    {
        return afterLast - first;
    }

    std::size_t size () const throw()
    {
        return static_cast<std::size_t> (ssize ());
    }

    const_iterator cbegin () const throw() { return first; }
    const_iterator  begin () const throw() { return first; }
          iterator  begin ()       throw() { return first; }
    const_iterator cend   () const throw() { return afterLast; }
    const_iterator  end   () const throw() { return afterLast; }
          iterator  end   ()       throw() { return afterLast; }

    const T & operator[] (std::size_t pos) const throw() { return first[pos]; }
          T & operator[] (std::size_t pos)       throw() { return first[pos]; }
};

template <typename T>
class ConstSpan
{
private:

    const T * first;
    const T * afterLast;

    ConstSpan<T> & operator= (const ConstSpan<T> &) { throw 0; } // disable

public:

    ConstSpan () throw()
        :
        first(nullptr),
        afterLast(nullptr)
    {}

    ConstSpan (const T * from, const T * afterTo) throw()
        :
        first(from),
        afterLast(afterTo)
    {}

    ConstSpan (Span<T> span) throw()
        :
        first(span.cbegin()),
        afterLast(span.cend())
    {}

    template <class C>
    explicit ConstSpan (const C & c) throw()
        :
        first(c.data()),
        afterLast(first+c.size())
    {}

    typedef const T * iterator;
    typedef const T * const_iterator;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    const T * data () const throw() { return first; }

    std::size_t size () const throw()
    {
        return static_cast<std::size_t> (afterLast - first);
    }

    const_iterator cbegin () const throw() { return first; }
    const_iterator  begin () const throw() { return first; }
    const_iterator cend   () const throw() { return afterLast; }
    const_iterator  end   () const throw() { return afterLast; }

    const T & operator[] (std::size_t pos) const throw() { return first[pos]; }
};

} // namespace cmbase64

#endif // __CPPMOVEBASE64_SPAN_H__

