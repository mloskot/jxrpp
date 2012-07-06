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
set(jpegxr_DIR ${CMAKE_SOURCE_DIR}/jxr-refsoft/src) 
set(jpegxr_SRC
	${jpegxr_DIR}/jpegxr.h
    ${jpegxr_DIR}/algo.c
    ${jpegxr_DIR}/api.c
    ${jpegxr_DIR}/cr_parse.c
    ${jpegxr_DIR}/cw_emit.c
    ${jpegxr_DIR}/flags.c
    ${jpegxr_DIR}/init.c
    ${jpegxr_DIR}/io.c
    ${jpegxr_DIR}/jpegxr_pixelformat.c
    ${jpegxr_DIR}/r_parse.c
    ${jpegxr_DIR}/r_strip.c
    ${jpegxr_DIR}/r_tile_frequency.c
    ${jpegxr_DIR}/r_tile_spatial.c 
    ${jpegxr_DIR}/w_emit.c
    ${jpegxr_DIR}/w_strip.c
    ${jpegxr_DIR}/w_tile_frequency.c
    ${jpegxr_DIR}/w_tile_spatial.c
    ${jpegxr_DIR}/x_strip.c)
if (MSVC)
    set_source_files_properties(${jpegxr_SRC} PROPERTIES LANGUAGE CXX)
    add_library(jpegxr STATIC ${jpegxr_SRC})
    set_target_properties(jpegxr PROPERTIES DEFINE_SYMBOL "JXR_DLL_EXPORTS")
else()
    add_library(jpegxr STATIC ${jpegxr_SRC})
endif()

###############################################################################
# libjxrpp
set(jxrpp_SRC jxrpp.hpp jxrpp.cpp)
add_library(jxrpp STATIC ${jxrpp_SRC})
set_target_properties(jxrpp PROPERTIES INCLUDE_DIRECTORIES ${jpegxr_DIR})

###############################################################################
# jxrpp_info
add_executable(jxrpp_info jxrpp_info.cpp)
set_target_properties(jxrpp_info PROPERTIES INCLUDE_DIRECTORIES ${jpegxr_DIR})
target_link_libraries(jxrpp_info jxrpp jpegxr)
