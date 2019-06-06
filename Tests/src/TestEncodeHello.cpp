/*
    TestEncodeHello.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <string>
#include <exception>

#include <CppMoveBase64.h>

static void testEncodeHello (const std::string & input,
                             const std::string & expectedOutput);

void testEncodeHello ()
{
    testEncodeHello ("Hello world!", "SGVsbG8gd29ybGQh");
    testEncodeHello ("Hello world!!", "SGVsbG8gd29ybGQhIQ==");
}

static void testEncodeHello (const std::string & input,
                             const std::string & expectedOutput)
{
    std::cout << "Text:   " << input << std::endl;

    auto output = cmbase64::encodeFromBin (
                            cmbase64::ConstSpan<char>(input));

    std::cout << "Base64: " << output.c_str() << std::endl;

    if (output.c_str() != expectedOutput)
        throw std::runtime_error ("The encoded string is wrong");
}
