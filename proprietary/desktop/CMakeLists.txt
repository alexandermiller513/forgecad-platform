# Copyright (c) 2026 Fintel IT Solutions LLC. All Rights Reserved.

cmake_minimum_required(VERSION 3.20)
project(forgecad_desktop LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(OpenCASCADE REQUIRED)

add_executable(forgecad_desktop
    main.cpp
    MainWindow.cpp
    OccView.mm
)

target_include_directories(forgecad_desktop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(forgecad_desktop
    PRIVATE
        Qt6::Widgets
        forgecad_occt_adapter
        TKernel
        TKMath
        TKBRep
        TKG3d
        TKGeomBase
        TKService
        TKV3d
        TKOpenGl
        TKPrim
        TKTopAlgo
)

if(APPLE)
    target_link_libraries(forgecad_desktop PRIVATE "-framework AppKit")
    set_source_files_properties(OccView.mm PROPERTIES COMPILE_FLAGS "-fno-objc-arc")
endif()

set_target_properties(forgecad_desktop PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
