# Motivation

This library is a practical application of the ideas I presented in:

+ https://www.mkrevuelta.com/en/2019/03/06/lets-make-easy-to-use-libraries-using-stdcpp-2019/

There is a less evolved proof of concept (no practical use, no exception handling) in:

+ https://github.com/mkrevuelta/CppLibraryInterfacePoC

CppMoveBase64 is a great C++ Base64 conversion library, but its functionality is a mere excuse. The main reason why I wrote it was to show, in a practical example, how to apply my ideas to make a C++ library with these compatibility characteristics (see [Why is this library special](../README.md#why-is-this-library-special)).

C++ and the Standard Library have evolved a lot recently. The ecosystem is growing faster and faster. Though, some of the main principles of C++ (best performance, general purpose, wildly varied platforms) prevent it from having a frozen, universally compatible ABI. Other languages sacrifice performance (and more) in exchange of a great degree of compatibility.

In C++ you can have compatibility problems between two pieces of a program just because they have been compiled with different compiler versions **from the same vendor!** Of course, compiler vendors make tremendous efforts not to break the compatibility. Though, from time to time, shit happens.

In open software the solution is relatively easy: "let the source be with you" and always compile everything with one compiler. 

Package managers like [Conan](https://conan.io) help by maintaining collections of binaries compiled with every version of every compiler.

One very acclaimed solution for proprietary software is the [Hourglass Pattern](https://es.slideshare.net/StefanusDuToit/cpp-con-2014-hourglass-interfaces-for-c-apis). But the Hourglass Pattern requires a huge effort from the library developer and **it just doesn't scale:** Let's say you have a library with an Hourglass interface, and you make another library that uses it. This new library can't expose, in its own interface, the classes it gets from the first library. It would need to pass everything through yet another Hourglass interface!

What I suffer "In Real Life" is that people are choosing to:
1. Write full C++ interfaces and distribute binaries compiled with one specific compiler version
2. Write pure C interfaces, but without the sweet C++ header-only layer of the Hourglass
3. Something in between

Option 1 ties the potential users to that specific compiler version. Option 2 brings twisted designs, performance loss, memory leaks and endless debugging sessions. Option 3 puts together the worst of option 1 and option 2.

Sometimes you can't choose the toolchain. Maybe you must use an old machine because you need a proprietary library which is installed and licensed only there. Maybe you don't have administrator permissions... That's life.

At the end of the day, **this problem is stopping people from using modern C++.** They are stuck with MSVC 2012 or GCC 4.8.5 because of some library provider or consumer (usually from the next department in the same corporation).

I am proposing to use some C++ in the library interfaces. This way we can make them efficient, easy to use and highly compatible.
