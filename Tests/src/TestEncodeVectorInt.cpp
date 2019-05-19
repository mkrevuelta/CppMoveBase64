#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include <CppMoveBase64.h>

void testEncodeVectorInt ()
{
    std::vector<int32_t> v;
    
    v.push_back (1);
    v.push_back (42);
    v.push_back (-3);
    v.push_back (0);
    v.push_back (-1);

    std::cout << "Numbers: ";
    for (int32_t i : v)
        std::cout << "  " << i;
    std::cout << std::endl;
    auto numsB64 = cmbase64::encode (v);
    std::cout << "Base64:  " << numsB64.c_str() << std::endl;

    if (std::string(numsB64.c_str()) != "AQAAACoAAAD9////AAAAAP////8=")
        throw std::runtime_error ("The encoded string is wrong");
}
