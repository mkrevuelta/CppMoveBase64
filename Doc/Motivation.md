# Motivation

This library is a practical application of the ideas I presented in:

+ https://www.mkrevuelta.com/en/2019/03/06/lets-make-easy-to-use-libraries-using-stdcpp-2019/

There is a less evolved proof of concept (no practical use, no exception handling) in:

+ https://github.com/mkrevuelta/CppLibraryInterfacePoC

It is a great C++ Base64 conversion library, but its functionality is a mere excuse. The main reason why I wrote it was to show, in a practical example, how to apply my ideas to make a C++ library with these compatibility characteristics (see the [README](../README.md)).

C++ and the Standard Library have evolved a lot recently. The ecosystem is growing faster and faster. Though, some of the main principles of C++ (best performance, general purpose, wildly varied platforms) prevent it from having a frozen, universally compatible ABI. Other languages sacrifice performance (and more) in exchange of a great degree of compatibility.

In C++ you can have compatibility problems between two pieces of a program just because they have been compiled with diferent compiler versions **from the same vendor**!. Of course, compiler vendors make tremendous efforts not to break the compatibility but from time to time... shit happens.

In open software the solution is relatively easy: "let the source be with you" and always compile everything with one compiler. 

Package managers like [Conan](https://conan.io) help by maintaining collections of binaries compiled with every version of every compiler.

_To be continued ..._
