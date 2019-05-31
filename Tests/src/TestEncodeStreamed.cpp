/*
    TestEncodeStreamed.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <sstream>
#include <string>
#include <exception>

#include <CppMoveBase64/Streamed.h>

static void testEncodeStreamed (std::size_t numBlocks);

void testEncodeStreamed ()
{
    testEncodeStreamed (0);
    testEncodeStreamed (1);
    testEncodeStreamed (2);
    testEncodeStreamed (10);
    testEncodeStreamed (1000);
}

static void testEncodeStreamed (std::size_t numBlocks)
{
    std::string hello ("Hello world!");
    std::cout << "Text:   " << hello << std::endl;

    std::stringstream iss;
    std::ostringstream oss;
    iss.write (hello.data(), hello.size());

    if (numBlocks > 0)
        cmbase64::encodeFromBinToB64Txt (iss, oss, numBlocks);
    else
        cmbase64::encodeFromBinToB64Txt (iss, oss);

    std::string helloB64 = oss.str ();
    std::cout << "Base64: " << helloB64.c_str() << std::endl;
    
    if (std::string(helloB64.c_str()) != "SGVsbG8gd29ybGQh")
        throw std::runtime_error ("The encoded string is wrong");
}
