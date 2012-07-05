###############################################################################
#
# Copyright (c) 2012 Mateusz Loskot <mateusz at loskot dot net>
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################
cmake_minimum_required(VERSION 2.6)
project(jxrpp)
set(jxrpp_VERSION_MAJOR 0)
set(jxrpp_VERSION_MINOR 1)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

###############################################################################
# libjpegxr - uses source files from git submodule jxr-refsoft
set(libjpegxr_DIR ${CMAKE_SOURCE_DIR}/jxr-refsoft/src)
set(libjpegxr_SRC
    ${libjpegxr_DIR}/algo.c
    ${libjpegxr_DIR}/api.c
    ${libjpegxr_DIR}/cr_parse.c
    ${libjpegxr_DIR}/cw_emit.c
    ${libjpegxr_DIR}/flags.c
    ${libjpegxr_DIR}/init.c
    ${libjpegxr_DIR}/io.c
    ${libjpegxr_DIR}/jpegxr_pixelformat.c
    ${libjpegxr_DIR}/r_parse.c
    ${libjpegxr_DIR}/r_strip.c
    ${libjpegxr_DIR}/r_tile_frequency.c
    ${libjpegxr_DIR}/r_tile_spatial.c 
    ${libjpegxr_DIR}/w_emit.c
    ${libjpegxr_DIR}/w_strip.c
    ${libjpegxr_DIR}/w_tile_frequency.c
    ${libjpegxr_DIR}/w_tile_spatial.c
    ${libjpegxr_DIR}/x_strip.c)
add_library(libjpegxr SHARED ${libjpegxr_SRC})
if (MSVC)
    set_source_files_properties(${libjpegxr_SRC} PROPERTIES LANGUAGE CXX)
    set_target_properties(libjpegxr PROPERTIES DEFINE_SYMBOL "JXR_DLL_EXPORTS")
endif()

###############################################################################
# libjxrpp
set(jxrpp_SRC jxrpp.hpp jxrpp.cpp)
add_library(libjxrpp STATIC ${jxrpp_SRC})
set_target_properties(libjxrpp PROPERTIES INCLUDE_DIRECTORIES ${libjpegxr_DIR})

###############################################################################
# jxrpp_info
add_executable(jxrpp_info jxrpp_info.cpp ${jxrpp_SRC} ${jpegxr_LIB})
set_target_properties(jxrpp_info PROPERTIES INCLUDE_DIRECTORIES ${libjpegxr_DIR})
target_link_libraries(jxrpp_info libjxrpp libjpegxr)