/*
    TestDecodeOldStyleHello.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <CppMoveBase64.h>

void testDecodeOldStyleHello ()
{
    std::string helloB64 ("SGVsbG8gd29ybGQh");

    std::cout << "Base64:   " << helloB64 << std::endl;

    std::size_t maxSize = cmbase64::decodedMaxSize (helloB64.size());
    std::vector<char> helloBinBuffer(maxSize+1);

    auto result = cmbase64::decodeFromB64TxtToBin (
                                cmbase64::ConstSpan<char>(helloB64),
                                cmbase64::Span<char>(helloBinBuffer));

    if (result.outcome != cmbase64::DecodeResult::Outcome::OkDone)
        throw std::runtime_error ("Decode returned an error");

    helloBinBuffer[result.size] = '\0';
    std::cout << "Text: " << helloBinBuffer.data() << std::endl;

    if (std::string(helloBinBuffer.data()) != "Hello world!")
        throw std::runtime_error ("The decoded string is wrong");
}
