# ABI

The binary frontier of CppMoveBase64 is simple enough to grant a high degree of compatibility.

It exposes C++ classes and functions, but:

1. No exceptions cross the frontier
2. No `std` classes are exposed
3. The only classes exposed have a very stable binary layout

Exceptions are handled like in a conventional hourglass pattern. In the library side they are converted to some kind of error state variables, and then some header-only code converts those errors back to exceptions in the client side. It's ugly, but I don't know any better option. Luckily, the ugliness stays inside the library.

It would be great if we could use `std::unique_ptr` and someday `std::span` (`span` is not yet standard; there's only a `gsl::span`).

`std::unique_ptr` probably contains has the same binary layout in every compiler out there: just one pointer, or two pointers in the custom-deleter flavour. Sadly, this layout is not standardized. It is probably a de-facto standard, but we can't rely on it.

One of the main `gsl` implementations out there stores `gsl::span` as a couple of pointers. Another one stores them as a pointer and a signed integer.

As a result, I had to implement my own `UniquePtr` and `Span` in this library.

`UniquePtr` contains just one pointer. The exposed classes `B64Txt` and `BinData` just contain a `UniquePtr`. They don't have any virtual function. Therefore, their binary layout is... just one pointer!

The other class exposed in the ABI is `DecIntermState`. It contains just an array of four chars.

There is no chance for different alignments or padding gaps between members. This ABI will be perfectly compatible between different compiler versions of a single vendor.

Not that I do not aim for compatibility between compilers of different vendors. That's another kettle of fish!

I also assume that you will need to compile separate binaries for 32-bit and 64-bit.
