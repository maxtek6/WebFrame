# This CMakeLists.txt is used by the vcpkg overlay port to build
# libcef_dll_wrapper from the CEF binary distribution source.
cmake_minimum_required(VERSION 3.15)
project(cef_dll_wrapper LANGUAGES CXX)

# Collect all wrapper source files
file(GLOB_RECURSE WRAPPER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/libcef_dll/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/libcef_dll/*.cpp"
)

# Exclude test sources
list(FILTER WRAPPER_SOURCES EXCLUDE REGEX ".*/test/.*")

# Exclude platform-specific sources that don't apply
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(FILTER WRAPPER_SOURCES EXCLUDE REGEX ".*_mac\\.mm$")
    list(FILTER WRAPPER_SOURCES EXCLUDE REGEX ".*_mac\\.cc$")
endif()
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(FILTER WRAPPER_SOURCES EXCLUDE REGEX ".*_win\\.cc$")
endif()

add_library(cef_dll_wrapper STATIC ${WRAPPER_SOURCES})

target_include_directories(cef_dll_wrapper
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
)

# CEF wrapper requires WRAPPING_CEF_SHARED to compile cpptoc/ctocpp sources
target_compile_definitions(cef_dll_wrapper PRIVATE WRAPPING_CEF_SHARED)

set_target_properties(cef_dll_wrapper PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(cef_dll_wrapper PRIVATE
        -Wno-undefined-var-template
        -Wno-missing-field-initializers
    )
endif()

install(TARGETS cef_dll_wrapper
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
