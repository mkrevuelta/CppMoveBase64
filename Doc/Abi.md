# ABI

The binary frontier of CppMoveBase64 is simple enough to grant a high degree of compatibility.

It exposes C++ classes and functions, but:

1. No exceptions cross the frontier
2. No `std` classes are exposed
3. The only classes exposed have a very stable binary layout
   * One pointer
   * Two pointers
   * An array of four chars
   * An `enum class` with `int8_t` as its underlying type

Exceptions are handled like in a conventional hourglass pattern. In the library side they are converted to some kind of error state variables, and then some header-only code converts those errors back to exceptions in the client side. It's ugly, but I don't know any better option. Luckily, the ugliness stays inside the library.

It would be great if we could use `std::unique_ptr` and someday `std::span` (`span` is not yet standard; there's only a `gsl::span` by now).

`std::unique_ptr` probably has the same binary layout in every compiler out there: just one pointer, or two pointers in the custom-deleter flavour. Sadly, this layout is not standardized. It is probably a de-facto standard, but we can't rely on it.

One of the main `gsl` implementations out there stores `gsl::span` as a couple of pointers. Another one stores them as a pointer and a signed integer.

As a result, I had to implement my own `UniquePtr` and `Span` in this library.

`UniquePtr` contains just one pointer. The exposed classes `B64Txt` and `BinData` just contain a `UniquePtr`. They don't have any virtual function. Therefore, their binary layout is... just one pointer!

`Span`, which is passed to or returned by several functions, contains just two pointers.

The other class exposed in the ABI is `DecIntermState` (_decoding intermediate state_). It contains just an array of four chars. I use this array to store zero, one, two or three bytes. One of the elements of the array is the counter indicating how many of the other bytes are in use. Again, this is another ugly trick, but the ugliness stays inside the library.

A few low-level functions return a value of type `ErrorStatus`, which is an `enum class` with `int8_t` as its underlying type. 

There is no chance for different alignments or padding gaps between members. This ABI will be perfectly compatible between different compiler versions of a single vendor.

Note that I do **not** aim for compatibility between compilers of **different vendors** with different mangling... That's entirely another kettle of fish!

I also assume that you will need to compile separate binaries for 32-bit and 64-bit.
