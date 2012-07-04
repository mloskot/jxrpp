#
# Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.6)
project(jxrcxx)
set(jxrcxx_VERSION_MAJOR 0)
set(jxrcxx_VERSION_MINOR 1)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()


set(jxrcxx_SRC jxrcxx.hpp jxrcxx.cpp)
set(jpegxr_LIB ${CMAKE_SOURCE_DIR}/lib/libjpegxr.a)
include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(jxrcxx_info jxrcxx_info.cpp ${jxrcxx_SRC} ${jpegxr_LIB})