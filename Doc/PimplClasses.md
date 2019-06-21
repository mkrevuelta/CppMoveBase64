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
 [`Span` and `ConstSpan`](Doc/UniquePtrAndSpan.md) for details on how to access the referred data.

In addition, `B64Text` has a `c_str()` member function that mimicks the `c_str()` of `std::string`. If the object is empty or in error state, `c_str()` just returns `""`.

The other functions of these classes implement the buffer allocation (`reserveAtLeast()`) and the actual encoding (`encodeFromBin()`) and decoding (`decodeFromB64Txt()`).

*To be continued...*
