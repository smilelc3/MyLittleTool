cmake_minimum_required(VERSION 3.16)
project(MyLittleTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)


# 使用Visual Studio编译额外的修改
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # 指定编译器的标准一致性模式(支持关键词：and or not)
    add_compile_options(/permissive-)
    # 指定代码文件编码格式为utf-8 (无BOM)
    add_compile_options(/utf-8)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Release")
    message (STATUS "No CMAKE_BUILD_TYPE selected, defaulting to ${CMAKE_BUILD_TYPE}")
endif ()

find_package(Threads REQUIRED)

add_executable(Hex2Ascii Hex2Ascii.cpp)
target_link_options(Hex2Ascii PRIVATE "-static")

add_executable(Ascii2Hex Ascii2Hex.cpp)
target_link_options(Ascii2Hex PRIVATE "-static")

add_executable(RamTest RamTest.cpp)

add_executable(DiskTest DiskTest.cpp)
add_executable(CheckEndian CheckEndian.cpp)

add_executable(Linear11Trans Linear11Trans.cpp)
target_link_options(Linear11Trans PRIVATE "-static")

add_executable(Linear16Trans Linear16Trans.cpp)
target_link_options(Linear16Trans PRIVATE "-static")

add_executable(ByteAcc checksum_byteacc.cpp)
target_link_libraries(ByteAcc PUBLIC Threads::Threads)
target_link_options(ByteAcc PRIVATE "-static")


add_executable(RandomMac RandomMac.cpp)

add_executable(Crc8 Crc8.c)
target_link_libraries(Crc8 PUBLIC Threads::Threads)

add_executable(DateTimeCalc DateTimeCalc.cpp)
target_link_options(DateTimeCalc PRIVATE "-static")

install(TARGETS Hex2Ascii DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS Ascii2Hex DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS RamTest DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS DiskTest DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS CheckEndian DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS Linear11Trans DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS Linear16Trans DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS ByteAcc DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS RandomMac DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS Crc8 DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS DateTimeCalc DESTINATION ${CMAKE_INSTALL_BINDIR})


