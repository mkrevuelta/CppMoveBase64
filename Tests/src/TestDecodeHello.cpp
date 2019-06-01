/*
    TestDecodeHello.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <string>
#include <exception>

#include <CppMoveBase64.h>

static void testDecodeHello (const std::string & input,
                             const std::string & expectedOutput);

void testDecodeHello ()
{
    testDecodeHello ("SGVsbG8gd29ybGQh", "Hello world!");
    testDecodeHello ("SGVsbG8gd29ybGQhIQ==", "Hello world!!");
}

static void testDecodeHello (const std::string & input,
                             const std::string & expectedOutput)
{
    std::cout << "Base64: " << input << std::endl;

    auto output = cmbase64::decodeFromB64Txt (
                            cmbase64::ConstSpan<char>(input));

    std::cout << "Text:   ";

    for (char c : output.span())
        std::cout << c;

    std::cout << std::endl;

    std::string copy (output.span().data(),
                      output.span().size());
    std::cout << "Copy:   " << copy << std::endl;

    if (copy != expectedOutput)
        throw std::runtime_error ("The encoded string is wrong");
}
