cmake_minimum_required (VERSION 2.8.9)

project (CppMoveBase64)

set (CMAKE_BUILD_TYPE Release)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
endif ()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/interface)

add_library (
    CppMoveBase64
    SHARED
    src/Encode.cpp
    src/Decode.cpp
    src/B64Text.cpp
    src/BinData.cpp)

set_target_properties (
    CppMoveBase64
    PROPERTIES
    CXX_VISIBILITY_PRESET hidden)

target_compile_definitions (
    CppMoveBase64
    PRIVATE
    COMPILING_CMBASE64)
