/*
    CppMoveBase64/DecIntermState.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#ifndef __CPPMOVEBASE64_DECINTERMSTATE_H__
#define __CPPMOVEBASE64_DECINTERMSTATE_H__

#include "ApiMacros.h"
#include "Span.h"

namespace cmbase64
{

namespace internal
{
    class DecIntermStateAccessor;
}

class CMBASE64_API DecIntermState
{
    friend class ::cmbase64::internal::DecIntermStateAccessor;

private:

    unsigned char countAndData[4];

    void setPending (ConstSpan<unsigned char> bytes);
    
    ConstSpan<unsigned char> getPending () const;

    void clear ()
    {
        countAndData[0] = 0;
    }

public:

    bool empty () const
    {
        return countAndData[0] == 0;
    }

    DecIntermState ()
    {
        clear ();
    }
};

} // namespace cmbase64

#endif // __CPPMOVEBASE64_DECINTERMSTATE_H__
