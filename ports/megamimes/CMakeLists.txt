cmake_minimum_required(VERSION 3.15)
project(megamimes VERSION 1.0.0 LANGUAGES C)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(megamimes STATIC src/MegaMimes.c)
add_library(megamimes::megamimes ALIAS megamimes)

target_include_directories(megamimes
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(TARGETS megamimes
    EXPORT megamimes-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(FILES src/MegaMimes.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT megamimes-targets
    FILE megamimes-targets.cmake
    NAMESPACE megamimes::
    DESTINATION share/cmake/megamimes
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/megamimes-config.cmake"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/megamimes-targets.cmake\")\n"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/megamimes-config.cmake"
    DESTINATION share/cmake/megamimes
)
