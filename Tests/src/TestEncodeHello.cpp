#include <iostream>
#include <string>
#include <exception>

#include <CppMoveBase64.h>

void testEncodeHello ()
{
    std::string hello ("Hello world!");
    std::cout << "Text:   " << hello << std::endl;
    auto helloB64 = cmbase64::encode (hello);
    std::cout << "Base64: " << helloB64.c_str() << std::endl;
    
    if (std::string(helloB64.c_str()) != "SGVsbG8gd29ybGQh")
        throw std::runtime_error ("The encoded string is wrong");
}
