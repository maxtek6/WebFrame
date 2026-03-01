cmake_minimum_required(VERSION 3.15)

project(webframe VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Libevent)

#add_library(webframe_core STATIC src/webframe_core.cpp)

#target_include_directories(webframe_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#add_library(webframe_desktop SHARED)

#add_library(webframe_browser SHARED)
