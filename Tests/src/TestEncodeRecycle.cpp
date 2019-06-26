/*
    TestEncodeRecycle.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <CppMoveBase64.h>

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
