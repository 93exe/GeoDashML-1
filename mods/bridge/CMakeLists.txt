cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Apple-specific settings. Android uses its own NDK toolchain.
if(APPLE AND NOT ANDROID)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gdml_bridge VERSION 0.2.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)

if(NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR
        "GEODE_SDK is not set. Point it at the Geode SDK checkout."
    )
endif()

message(STATUS "Found Geode SDK: $ENV{GEODE_SDK}")

add_subdirectory(
    $ENV{GEODE_SDK}
    ${CMAKE_CURRENT_BINARY_DIR}/geode
)

setup_geode_mod(${PROJECT_NAME})
