/*
    TestDecodeStreamed.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <sstream>
#include <string>
#include <exception>

#include <CppMoveBase64/Streamed.h>

static void testDecodeStreamed (std::size_t numBlocks);

void testDecodeStreamed ()
{
    testDecodeStreamed (0);
    testDecodeStreamed (1);
    testDecodeStreamed (2);
    testDecodeStreamed (10);
    testDecodeStreamed (1000);
}

static void testDecodeStreamed (std::size_t numBlocks)
{
    std::string helloB64 ("SGVsbG8gd29ybGQh");
    std::cout << "Base64:   " << helloB64 << std::endl;

    std::stringstream iss;
    std::ostringstream oss;
    iss.write (helloB64.data(), helloB64.size());

    if (numBlocks > 0)
        cmbase64::decodeFromB64TxtToBin (iss, oss, numBlocks);
    else
        cmbase64::decodeFromB64TxtToBin (iss, oss);

    std::string hello = oss.str ();
    std::cout << "Text: " << hello << std::endl;

    if (hello != "Hello world!")
        throw std::runtime_error ("The encoded string is wrong");
}
