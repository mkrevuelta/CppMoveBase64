# API Macros

A few macros are conditionally defined in `<CppMoveBase64/ApiMacros.h>`. Their specific definition depends on:
+ the compiler brand
+ the macro `COMPILING_CMBASE64`, which is supposed to be defined only while compiling the library, and **not** while compiling client code.

The macros are:
* `CMBASE64_API`, which marks the classes and free fuctions that are exposed in the library interface
* `EXTERN_TO_ALL_BUT_CMBASE64`, defined as the keyword `extern` for client code, and nothing for the library if compiled with MSVC. This macro is used to restrict the instantiation of some templates, thus ensuring that their code is on the library side

Finally, the macro `CMBASE64_NOEXCEPT` plays the role of what I wish would be `noexcept`, but is actually `trow()` for backward compatibility.
