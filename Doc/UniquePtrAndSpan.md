# UniquePtr and Span

`UniquePtr`, `Span` and `ConstSpan` are the cornerstones of CppMoveBase64's intenface. They are key to the stability of its ABI.

## UniquePtr

`UniquePtr` is used in the PIMPL classes exposed in the interface. It is a simplified version of std::unique_ptr.

The main differences are:
1. `UniquePtr` doesn't have a `reset()` function and it can't be constructed from a raw pointer. Allocation and deallocation of the pointed object can only be done by specific functions compiled only in the library. Thus, there's no way to `new` on one side and `delete` on the other.
2. Its simple implementation imposes some restrictions. There is no constuctor  with parameters forwarding and the pointed class must be default-constructible.

`UniquePtr` contains just one member: a pointer.

## Span and ConstSpan

These classes serve as "views" of data arrays stored in contiguous memory (i.e. `std::vector`, `std::array`, or conventional arrays).

The concept is very similar to `gsl::span`. The data can be accessed as if they were vectors. Their interface provides:
+ `data()` and `size()`
+ `begin()` and `end()` (which enable the use of range-based for loops)
+ `operator[]`

Note that objects of type `Span` or `ConstSpan` don't really own the pointed memory. You must make sure that you don't try to use the `Span` after the destruction of the object that actually owned the data. See [Beware of the dangling Spans](/Doc/DanglingSpans.md).

Regarding interfaces, the problem of `gsl::span` is that it can be (and is!) implemented in several, ABI-incompatible ways. `Span` just contains two pointers that act as `begin` and `end` of the sequence. `ConstSpan` is nearly identical and works with const data.
