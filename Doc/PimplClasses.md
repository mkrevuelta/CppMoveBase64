# The PIMPL classes: B64Text and BinData

The class `B64Text` represents the result of encoding some binary data to base64.

The class `BinData` represents the result of decoding from base64 to binary.

They both are PIMPL classes with move semantics. Furthermore, they are *move-only*; they can't be copied via copy construction or copy assignment.

They can hold either:
+ a valid result, **or**
+ some error state information, **or**
+ nothing! (if just default-constructed or moved-from)

The error status can be queried via the member functions:

```C++
bool isOk () const;
bool isError () const;
const char * errorMessage () const;
```

`BinData` has another function `isFinishedOk()` for special use cases.

The actual result, if any, can be obtained with the member functions:

```C++
     Span<char> span ();
ConstSpan<char> span () const;
```

See 
 [`Span` and `ConstSpan`](/Doc/UniquePtrAndSpan.md) for details on how to access the referred data.

In addition, `B64Text` has a `c_str()` member function that mimicks the `c_str()` of `std::string`. If the object is empty or in error state, `c_str()` just returns `""`.

The other functions of these classes implement the buffer allocation (`reserveAtLeast()`) and the encoding (`encodeFromBin()`) to a `B64Text` and decoding (`decodeFromB64Txt()`) to a `BinData`. These functions are part of the library's binary interface. For this reason, they never throw exceptions. Instead, they set the error state of the object.

For obvious convenience, other inline, header-only functions are provided: `cmbase64::encodeFromBin()` and `cmbase64::decodeFromB64Txt()`. They call the member functions described above, check the error condition and, if necessary, throw exceptions (from the client's side!). See the usage examples in [README.md](/README.md).

Interestingly enough, `B64Text::encodeFromBin()` and `BinData::decodeFromB64Txt()` don't implement directly the encoding and decoding algorithms. They just allocate the required space and then they call another two functions that do the real work: `cmbase64::encodeFromBinToB64Txt()` and `cmbase64::decodeFromB64TxtToBin()`. These functions receive the source and destination buffers by reference as Spans and never throw exceptions.
