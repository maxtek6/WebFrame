option(BUILD_TESTING "Build testing" OFF)
option(BUILD_RUNTIME "Build runtime" ON)
option(BUILD_EXAMPLE "Build example" OFF)
option(BUILD_DOXYGEN "Build doxygen documentation" OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/webframe.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/configure.cmake)

if(NOT VCPKG_ROOT)
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    if(NOT VCPKG_ROOT)
        message(FATAL_ERROR "VCPKG_ROOT environment variable is not set. Please set it to the root of your vcpkg installation.")
    endif()
endif()

configure_vcpkg_features()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required(VERSION 3.15)

project(webframe VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_packages()

add_subdirectory(src)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()