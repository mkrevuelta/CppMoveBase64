# PIMPL macros

The header `PimplMacros.h` defines a few helper macros that allow us to write a correct PIMPL class in the blink of an eye, reducing the visual bloat of boilerplate code and letting the payload code outstand.

## Minimal usage

The minimal usage requires the macros:
+ `CMBASE64_DECLARE_MOVE_ONLY_PIMPL`
+ `CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL`

We would declare our PIMPL class in its header file (the `.h`) as follows:
```C++
class CMBASE64_API MyPimpl
{
    CMBASE64_DECLARE_MOVE_ONLY_PIMPL (MyPimpl)

public:
    // Interface functions...
};
```

Then, in the implementation file (the `.cpp`) we would write:
```C++
struct MyPimpl::Impl
{
    // Payload data...
};
 CMBASE64_IMPLEMENT_MOVE_ONLY_PIMPL (MyPimpl)

// Implementation of interface functions
```

The struct `Impl` holds the actual payload. It must have that name and it has to be nested inside `MyPimpl`. The most important requirement is that it must be default-constructible.

You can put anything inside `MyPimpl::Impl`: a `std::vector`, a `std::string`, a `std::map` or some class of your own. This struct is only visible from inside this `.cpp` and is **not** part of the interface.

Then you would implement the interface functions of `MyPimpl`. These functions should receive or return only *safe* (ABI-stable) types: `int`, `double`, `char*`, `Span`, `ConstSpan`...

The interface functions of `MyPimpl` can use the member `pImpl` to access the `Impl` struct. Though, they must take into account that `pImpl` might be empty. In that case, they must call `allocate()` or operate with some default value. Note that `allocate()` might throw exceptions.

Interface functions should never throw exceptions. Therefore, if they call allocate, they should catch any possible exception and report it by means of some return value and/or the other member of the PIMPL class: `status`.

## Symmetric swap

The `_DECLARE_` and `_IMPLEMENT_` macros provide a `swap` member function, but it is also good to have a `swap` function outside of the class. The macro `CMBASE64_INLINE_SYMMETRIC_SWAP` helps providing that.

## Copyable PIMPLs

If required, you could make the PIMPL copyable by using the `_COPYABLE_` versions of the macros instead of the `_MOVE_ONLY_` versions. Of course, your `MyPimpl::Impl` would need to be copyable in that case.

## Nested PIMPL classes

The macros also support the creation of nested (`_INNER_`) classes. Though, I discarded using them after a few experiments.
