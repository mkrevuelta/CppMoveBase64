/*
    DecIntermState.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64/DecIntermState.h>
#include <CppMoveBase64.h>

namespace cmbase64
{

void DecIntermState::setPending (ConstSpan<unsigned char> pending)
{
    std::size_t size = pending.size ();

    if (size > 3)
        size = 3;

    const unsigned char * src = pending.cbegin ();

    countAndData[0] = static_cast<unsigned char> (size);

    for (unsigned i=1; i<=size; i++)
        countAndData[i] = *(src++);
}

ConstSpan<unsigned char> DecIntermState::getPending () const
{
    return ConstSpan<unsigned char>(
                countAndData + 1,
                countAndData + 1 + countAndData[0]);
}

} // namespace cmbase64
