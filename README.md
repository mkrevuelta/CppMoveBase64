# CppMoveBase64
Base64 encoder/decoder for C++ 11 and above (move semantics, yet highly compatible across compiler versions)

## Current status

![CppMoveBase64 build status](https://api.travis-ci.com/mkrevuelta/CppMoveBase64.png "CppMoveBase64 build status")  See details in [Travis-CI](https://travis-ci.com/mkrevuelta/CppMoveBase64)

* Functionality has just been completed (as of 2019/06/01)
* Tests are only running the basic stuff
* **Feedback is appreciated**

## Why is this library special?

1. It has a C++ 11 interface that takes benefit from **move semantics**
   * Client code can be sound and clear, as in `y = f(x);`
   * No unnecesary copies of the data will be made

2. It is **highly compatible** across compiler versions
   * You can compile the library with, let's say, MSVC 2012...
   * ...and then use it in a program compiled in MSVC 2019...
   * ...**or vice-versa!** Yes: I can develop my library with the latest, cutting edge compiler version, even though my client keeps using an old compiler

3. This compatibility **scales** as the number of libraries grows. It is **transitive**
   * Let's say you create a compression library FooZip that uses CppMoveBase64
   * FooZip can simply expose CppMoveBase64's objects in its own interface
   * Objects provided by CppMoveBase64 can be passed around safely from one library/program to another, even though each one has been generated with a different version of the compiler

## Basic encoding usage

```C++
std::string binaryData("Hello world!!");

std::cout << "Text:   " << binaryData << std::endl;

auto b64Text = cmbase64::encodeFromBin (
                   cmbase64::ConstSpan<char>(binaryData));

std::cout << "Base64: " << b64Text.c_str() << std::endl;
```

The input in this example is a `std::string` just for the sake of clarity and simplicity. You can replace it with a `std::vector`, a `std::array`, or anything with `data()` and `size()` on its interface.

Oh, and the elements can be of type `char`, `unsigned char`, or any fundamental type (`int`, `double`...). However, note that if you use multi-byte elements, endianness does matter.

The code fragment above prints:
```
Text:   Hello world!!
Base64: SGVsbG8gd29ybGQhIQ==
```

## Basic decoding usage

```C++
std::string b64Text("SGVsbG8gd29ybGQhIQ==");

std::cout << "Base64: " << b64Text << std::endl;

auto binaryData = cmbase64::decodeFromB64Txt (
                      cmbase64::ConstSpan<char>(b64Text));

std::cout << "Text:   ";

for (char c : binaryData.span())
    std::cout << c;

std::cout << std::endl;
```

The code fragment above prints:
```
Base64: SGVsbG8gd29ybGQhIQ==
Text:   Hello world!!
```

The resulting object `binaryData` contains `char` elements. You can access them througth the `span()` function. For example, you could construct a `std::string` copying the data:
```
std::string binaryString (binaryData.span().data(),
                          binaryData.span().size());
```

If you need to decode to other fundamental types (`int`, `double`...), then you can use `cmbase64::decodeFromB64TxtToBin()` instead.

## How to compile and test

In Windows, with MSVC:
```
C:\...\CppMoveBase64> mkdir build

C:\...\CppMoveBase64> cd build

C:\...\CppMoveBase64\build> cmake ..
[..]
C:\...\CppMoveBase64\build> cmake --build .
[..]
C:\...\CppMoveBase64\build> ctest
[..]
100% tests passed, 0 tests failed out of 6
```

If you have several MSVC versions installed, you can specify one of them in the first `cmake` call:
```
C:\...\CppMoveBase64\build> cmake -G "Visual Studio 11 2012" ..
```

In Linux you can use the same commands, but instead of `cmake --build .` you might prefer to directly run `make`, which will preserve the nice colors of the compiler output.

## More details

### Rationale and design

* [Motivation](Doc/Motivation.md)
* [The ABI](Doc/Abi.md)
* [`UniquePtr`, `Span` and `ConstSpan`](Doc/UniquePtrAndSpan.md)
* [API macros](Doc/ApiMacros.md)
* [PIMPL macros](Doc/PimplMacros.md)
* [The PIMPL classes](Doc/PimplClasses.md)

### Advanced usage

* [Recycling buffers](Doc/RecyclingBuffers.md)
* Low level conversion with client-provided buffers *(docs in progress...)*
* Stream conversion *(docs in progress...)*
