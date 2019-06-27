# Low level conversion with client-provided buffers

The classes `B64Text` and `BinData` make this library special, different from any other base64 library out there (see why in the [README](/README.md)).

That said, it is a base64 library, after all. There is no reason to hide the raw, low level conversion functions:

```C++
CMBASE64_API void encodeFromBinToB64Txt (
                    ConstSpan<char> binSrc,
                    Span<char> textDest)
                            throw();

CMBASE64_API DecodeResult decodeFromB64TxtToBin (
                    ConstSpan<char> textSrc,
                    Span<char> binDest,
                    DecIntermState * intermState = nullptr,
                    bool toBeContinued = false)
                            throw();
```

The struct `DecodeResult` is defined as follows:

```C++
struct DecodeResult
{
    enum class Outcome : intptr_t
    {
        OkDone, OkPartial, DestSpanIsTooSmall, InvalidInput
    };

    std::size_t size;
    Outcome outcome;
};
```

You can use these functions to encode/decode to/from vectors, arrays or any contiguous memory containers. Just use Spans to pass them references to your buffers (see [UniquePtr and Span](/Doc/UniquePtrAndSpan.md) for more details).

The next two functions help by computing the required size for the output:

```C++
inline std::size_t encodedSize (std::size_t binSrcSizeInBytes) throw();

inline std::size_t decodedMaxSize (std::size_t b64TextSrcSizeInChars) throw();
```

If you want to encode a long binary message block by block, you must make sure that every block, except perhaps the last one, has a length multiple of three bytes. Otherwise you would get '`=`' characters at the end of intermediate blocks, and the concatenated outputs wouldn't make a legal base64 string.

The decoding interface is a bit more complex because base64 text might contain spaces, tabs and newlines. Thus, the estimation of the space required is not completely precise. Hence the "Max" in `decodedMaxSize()`. Furthermore, cutting the base64 string in pieces of length multiple of four characters would be time consuming (comparable to the decoding itself). For this reason, `decodeFromB64TxtToBin()` takes a pointer to an object that holds an intermediate state: the bits of a possibly incomplete four-characters pack at the end of the block. It takes from there the remains of a previous block, if any, and leaves the remains of the current block, if any. The parameter `toBeContinued` should be set to `true` for every block except for the last one.
