# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

cmake_minimum_required(VERSION 3.20)
project(forgecad_occt_adapter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(forgecad_occt_adapter SHARED
    src/occt_adapter.cpp
)

target_include_directories(forgecad_occt_adapter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

find_package(OpenCASCADE REQUIRED)

target_link_libraries(forgecad_occt_adapter
    PUBLIC
        TKernel
        TKMath
        TKBRep
        TKGeomBase
        TKG3d
        TKTopAlgo
        TKPrim
        TKDESTEP
)

target_compile_definitions(forgecad_occt_adapter PUBLIC FORGECAD_OCCT_LINKED=1)

if(APPLE)
    target_compile_options(forgecad_occt_adapter PRIVATE -fPIC)
endif()
