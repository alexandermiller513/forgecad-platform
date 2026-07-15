# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

cmake_minimum_required(VERSION 3.20)
project(forgecad_occt_adapter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OCCT_ROOT "${CMAKE_SOURCE_DIR}/../../third-party/occt" CACHE PATH "OCCT source root")

add_library(forgecad_occt_adapter SHARED
    src/occt_adapter.cpp
)

target_include_directories(forgecad_occt_adapter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Dynamic linking to OCCT — configure OCCT_DIR or OCCT_INSTALL_PREFIX at build time.
find_package(OpenCASCADE QUIET)
if(OpenCASCADE_FOUND)
    target_link_libraries(forgecad_occt_adapter PRIVATE TKernel TKMath TKBRep TKSTEP)
    target_compile_definitions(forgecad_occt_adapter PRIVATE FORGECAD_OCCT_LINKED=1)
endif()
