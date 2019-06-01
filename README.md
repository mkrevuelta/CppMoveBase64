# CppMoveBase64
Base64 encoder/decoder for C++ 11 and above (move semantics, yet highly compatible across compiler versions)

![CppMoveBase64 build status](https://api.travis-ci.com/mkrevuelta/CppMoveBase64.png "CppMoveBase64 build status") See in [Travis-CI](https://travis-ci.com/mkrevuelta/CppMoveBase64)

## Why is this library special?

1. It has a C++ 11 interface that takes benefit from **move semantics**
   * Client code can be sound and clear, as in `y = f(x);`
   * No unnecesary copies of the data will be made

2. It is **highly compatible** across compiler versions
   * You can compile the library with, let's say, MSVC 2019...
   * ...and then use it in a program compiled in MSVC 2012...
   * ...or vice-versa!

3. This compatibility **scales** as your project grows
   * Let's say you use this library and some other libraries in your program...
   * Then, objects provided by CppMoveBase64 can travel around safely from one library/program to another, even though each one has been generated with a different version of the compiler
