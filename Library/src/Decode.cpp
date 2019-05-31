/*
    Decode.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64.h>
#include <CppMoveBase64/ErrorStatus.h>

namespace cmbase64
{

//-- Tables


//-- additional parameter for intermediate decoding bytes
CMBASE64_API DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<char> binDest)
                            CMBASE64_NOEXCEPT
{
    DecodeResult result;

    std::size_t size = textSrc.size ();
    std::size_t destCapacity = binDest.size ();

    const char * src = textSrc.begin ();
    auto dst = reinterpret_cast<unsigned char *> (
                                        binDest.begin ());


    //--
    result.size = 0;
    result.outcome = DecodeResult::Outcome::OkPartial;

    return result;
}

} // namespace cmbase64
