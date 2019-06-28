# Stream conversion

The header `<CppMoveBase64/Streamed.h>` is not included by `<CppMoveBase64.h>`. If you want to use it, you have to include it explicitly.

This header defines two inline functions that implement the streamed encoding and decoding:

```C++
inline void encodeFromBinToB64Txt (
                std::istream & is,
                std::ostream & os,
                std::size_t numBlocks = 0);

inline void decodeFromB64TxtToBin (
                std::istream & is,
                std::ostream & os,
                std::size_t numBlocks = 0);
```

These functions read from the input stream `is`, translating on the fly and writing to the output stream `os` until the input is completely consumed (the "end of file" is reached) or an error occurs.

They translate buffers of `numBlocks` three-byte packs (four-character packs, in base64). The value `numBlocks=0` indicates some default size.

The error reporting in these functions is a bit immature. Particularly, the decoding function doesn't signal errors related to invalid input characters. The stream related errors, at least, can be checked by the caller after the functions return.
