# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

cmake_minimum_required(VERSION 3.20)
project(fintel_forgecad LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Prefer a local OCCT install produced by scripts/build-occt.sh
set(FORGECAD_OCCT_INSTALL "${CMAKE_SOURCE_DIR}/build/occt-install" CACHE PATH
    "OCCT install prefix from scripts/build-occt.sh")
if(EXISTS "${FORGECAD_OCCT_INSTALL}")
    list(PREPEND CMAKE_PREFIX_PATH "${FORGECAD_OCCT_INSTALL}")
    if(EXISTS "${FORGECAD_OCCT_INSTALL}/lib/cmake/opencascade")
        set(OpenCASCADE_DIR "${FORGECAD_OCCT_INSTALL}/lib/cmake/opencascade"
            CACHE PATH "OpenCASCADE CMake package dir" FORCE)
    endif()
endif()

find_package(OpenCASCADE REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

message(STATUS "OpenCASCADE include dirs: ${OpenCASCADE_INCLUDE_DIR}")
message(STATUS "Building Fintel IT ForgeCAD desktop CAD client")

add_subdirectory(proprietary/occt-adapter)
add_subdirectory(proprietary/desktop)
