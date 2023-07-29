cmake_minimum_required(VERSION 3.16)
project(Hex2Ascii)

set(CMAKE_CXX_STANDARD 14)


# 使用Visual Studio编译额外的修改
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # 指定编译器的标准一致性模式(支持关键词：and or not)
    add_compile_options(/permissive-)
    # 指定代码文件编码格式为utf-8 (无BOM)
    add_compile_options(/utf-8)
endif ()


add_executable(Hex2Ascii Hex2Ascii_main.cpp)
add_executable(Ascii2Hex Ascii2Hex_main.cpp)

add_executable(RamTest ram_test_main.cpp)
add_executable(Linear11Trans Linear11Trans.cpp)
add_executable(Linear16Trans Linear16Trans.cpp)
add_executable(CheckEndian CheckEndian.cpp)


install(TARGETS Hex2Ascii DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS Ascii2Hex DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS RamTest DESTINATION ${CMAKE_INSTALL_LIBDIR})
