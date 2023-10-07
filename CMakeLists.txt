cmake_minimum_required(VERSION 3.26)
project(lcppd)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/vendor
)

include_directories(
        $ENV{DXSDK_DIR}/Include
)

file(GLOB all_SRCS
        ${PROJECT_SOURCE_DIR}/src/dllmain.cpp
)

file(GLOB all_VNDRS
        ${PROJECT_SOURCE_DIR}/vendor/iv-sdk/include/**/*.h
        ${PROJECT_SOURCE_DIR}/vendor/iv-sdk/include/*.cpp
)

set(CMAKE_CXX_FLAGS "/utf-8")
set(CMAKE_C_FLAGS "/utf-8")


add_definitions(-D_UNICODE)
add_definitions(-DCMAKE_GENERATOR_PLATFORM=Win64)

add_library(lcppd SHARED ${all_SRCS})

set_target_properties(lcppd PROPERTIES SUFFIX ".asi")