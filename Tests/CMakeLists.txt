cmake_minimum_required (VERSION 2.8.9)

project (Tests)

set (CMAKE_BUILD_TYPE Release)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
endif ()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../Library/interface)

add_executable (
    Tests
    src/main.cpp
    src/TestEncodeHello.cpp
    src/TestEncodeVectorInt.cpp
    src/TestEncodeStreamed.cpp
    src/TestEncodeRecycle.cpp
    src/TestDecodeHello.cpp
    src/TestDecodeStreamed.cpp
    src/TestDecodeOldStyleHello.cpp)

target_link_libraries (
    Tests
    CppMoveBase64)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_custom_command (
        TARGET Tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/Library/\$\(Configuration\)/CppMoveBase64.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/\$\(Configuration\)/")
endif ()

add_test (EncodeHello     Tests EncodeHello)
add_test (EncodeVectorInt Tests EncodeVectorInt)
add_test (EncodeStreamed  Tests EncodeStreamed)
add_test (EncodeRecycle   Tests EncodeRecycle)

add_test (DecodeHello     Tests DecodeHello)
add_test (DecodeStreamed  Tests DecodeStreamed)

add_test (DecodeOldStyleHello  Tests DecodeOldStyleHello)
