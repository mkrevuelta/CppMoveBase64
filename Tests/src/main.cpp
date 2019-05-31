/*
    main.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <iostream>
#include <string>
#include <exception>

#include <CppMoveBase64.h>

void testEncodeHello ();
void testEncodeVectorInt ();
void testEncodeStreamed ();

struct
{
    const char * name;
    void (* function) ();
}
testsTable [] =
{
    { "EncodeHello",     testEncodeHello },
    { "EncodeVectorInt", testEncodeVectorInt },
    { "EncodeStreamed",  testEncodeStreamed },

    { "TABLE END", nullptr }
};

const char * allTestsName = "All";

int main (int argc, const char * argv[])
{
    try
    {
        if (argc != 2)
            throw std::runtime_error ("Error: incorrect parameters");

        std::string testName (argv[1]);

        unsigned count = 0;

        for (unsigned i=0; testsTable[i].function; i++)
            if (testName==allTestsName || testName==testsTable[i].name)
            {
                std::cout << std::string (40, '=') << std::endl;

                std::cout << "Running test "
                          << testsTable[i].name << std::endl;

                testsTable[i].function ();

                count ++;
            }

        std::cout << std::string (40, '=') << std::endl;
        std::cout << "Total: " << count << " test(s)" << std::endl;

        if (count == 0)
            throw std::runtime_error ("Error: unknown test " +
                                      testName);
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what () << std::endl;
        throw;
    }

    return 0;
}
