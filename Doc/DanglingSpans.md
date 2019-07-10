# Beware of the dangling Spans

[`Span` and `ConstSpan`](Doc/UniquePtrAndSpan.md) objects just contain pointers that refer to memory owned by some other objects. When you use a Span to access that memory you must be sure that it's still there. That is, you must make sure that the owner object hasn't been destroyed and the memory hasn't been deallocated.

Let's take, for instance, this fragment of code:

```C++
{
    std::string b64Text("SGVsbG8gd29ybGQhIQ==");

    auto binaryData = cmbase64::decodeFromB64Txt (
                          cmbase64::ConstSpan<char>(b64Text));

    for (char c : binaryData.span())
        std::cout << c;
        
}   // <--- binaryData is destroyed here
```

Suppose that we change the code as follows:

```C++
{
    std::string b64Text("SGVsbG8gd29ybGQhIQ==");

    auto binDataSpan = cmbase64::decodeFromB64Txt (
                           cmbase64::ConstSpan<char>(b64Text))
                               .span ();

    for (char c : binDataSpan)
        std::cout << c;        // UNDEFINED BEHAVIOUR!!!
}
```

The object returned by `cmbase64::decodeFromB64Txt()` is a temorary object, and now it is not stored anywhere. The expression in the `binDataSpan` initialization is evaluated, and then the temporary is destroyed. Thus, `binDataSpan` points to something that is not there anymore. It is a dangling Span.

In case you are wondering, you can safely move PIMPL objects and keep on using Spans that you obtained previously. Since they are PIMPL objects, the actual memory buffers are not reallocated by move operations.
