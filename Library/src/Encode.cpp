/*
    Encode.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppMoveBase64
*/

#include <CppMoveBase64.h>

namespace cmbase64
{

static const char table[64] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

    '+', '/'
};

CMBASE64_API void encode (ConstSpan<char> binData, char * dst)
                                                CMBASE64_NOEXCEPT
{
    std::size_t size = binData.size ();
    auto src = reinterpret_cast<const unsigned char *> (
                                                    binData.begin ());
    std::size_t tailSize = size % 3;

    if (size >= 3)
    {
        const unsigned char * endBlocks = src + (size - tailSize);

        do
        {
            dst[0] = table[  (src[0] >> 2) & 0x3F ];

            dst[1] = table[ ((src[0] << 4) & 0x30) |
                            ((src[1] >> 4) & 0xF)    ];

            dst[2] = table[ ((src[1] << 2) & 0x3C) |
                            ((src[2] >> 6) & 0xF)    ];

            dst[3] = table[   src[2] & 0x3F ];

            src += 3;
            dst += 4;
        }
        while (src != endBlocks);
    }

    if (tailSize == 2)
    {
        dst[0] = table[  (src[0] >> 2) & 0x3F ];

        dst[1] = table[ ((src[0] << 4) & 0x30) |
                        ((src[1] >> 4) & 0xF)    ];

        dst[2] = table[  (src[1] << 2) & 0x3C ];

        dst[3] = '=';

        dst += 4;
    }
    else if (tailSize == 1)
    {
        dst[0] = table[ (src[0] >> 2) & 0x3F ];

        dst[1] = table[ (src[0] << 4) & 0x30 ];

        dst[2] = '=';
        dst[3] = '=';

        dst += 4;
    }

    dst[0] = '\0';
}

} // namespace cmbase64
