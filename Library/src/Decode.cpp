/*
    Decode.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64.h>

namespace cmbase64
{

//-- Tables

//-- return enum indicating state
//-- additional parameter for intermediate decoding bytes
CMBASE64_API void decode (
                    ConstSpan<char> textSrc,
                    Span<char> binDest)
                            CMBASE64_NOEXCEPT
{
    std::size_t size = textSrc.size ();
    std::size_t destCapacity = binDest.size ();

    if (destCapacity == 0)
        return;

    const char * src = textSrc.begin ();
    auto dst = reinterpret_cast<unsigned char *> (
                                        binDest.begin ());

    if (destCapacity < encodedSize(size))
    {
        dst[0] = '\0';
        return;
    }

    //--
}

} // namespace cmbase64
