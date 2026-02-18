cmake_minimum_required(VERSION 3.15)

project(webframe VERSION 0.1.0)

add_library(webframe_shell STATIC src/shell/shell.cpp)

add_library(webframe_desktop SHARED)

add_library(webframe_browser SHARED)
