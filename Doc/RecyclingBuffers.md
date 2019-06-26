# Recycling buffers

The basic usage proposed in the [README](README.md) allocates a new object with its own buffer in every encoding/decoding call.

If you need to, you can save allocations by recycling `B64Text` and/or `BinData` objects.

The trick consists in calling the member encode/decode functions instead of the free ones. As a side effect, you will need to check the resulting status after every encoding/decoding operation, because these functions never throw exceptions.

The code below illustrates this possibility:
```C++
void testEncodeRecycle ()
{
    cmbase64::B64Text output;
    std::string input;

    // First, encode a medium-sized input

    input = "Some binary data";

    std::cout << "Text:   " << input << std::endl;

    // Will reserve just required space for current input
    output.encodeFromBin (cmbase64::ConstSpan<char>(input));

    if (output.isError())
        throw std::runtime_error (output.errorMessage());

    std::cout << "Base64: " << output.c_str() << std::endl;
    
    if (output.c_str() != std::string("U29tZSBiaW5hcnkgZGF0YQ=="))
        throw std::runtime_error ("The encoded string is wrong");

    // Then, encode a slightly smaller input

    input = "Small data";

    std::cout << "Text:   " << input << std::endl;

    // No need to reserve space this time
    output.encodeFromBin (cmbase64::ConstSpan<char>(input));

    if (output.isError())
        throw std::runtime_error (output.errorMessage());

    std::cout << "Base64: " << output.c_str() << std::endl;

    if (output.c_str() != std::string("U21hbGwgZGF0YQ=="))
        throw std::runtime_error ("The encoded string is wrong");
}
```

Every successive call to `B64Text::encodeFromBin()` will reuse, if possible, the buffer allocated previously. If the result doesn't fit, it will automatically allocate more space.

I you know in advance the maximum size required, you can call `B64Text::reserveAtLeast()`, thus ensuring that no later reallocation will take place.

All this applies to `BinData` as well.
