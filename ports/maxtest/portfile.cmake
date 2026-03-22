vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO maxtek6/maxtest
    REF master
    SHA512 ad470249867d8f4d915e2c0b89f1ff4b62fef9d0202e402fa8b7ac2cff457181f5e45cde7fbc33d1282d045778e2485a0d2929563624fbdc67cff96ce943aea2
    HEAD_REF master
)

# maxtest is header-only, just install the header file
file(INSTALL "${SOURCE_PATH}/maxtest.hpp"
     DESTINATION "${CURRENT_PACKAGES_DIR}/include")

# Create CMake config files for find_package support
file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/lib/cmake/maxtest")

file(WRITE "${CURRENT_PACKAGES_DIR}/lib/cmake/maxtest/maxtest-config.cmake"
"
include_guard(GLOBAL)

add_library(maxtest INTERFACE)
target_include_directories(maxtest INTERFACE
    \$<BUILD_INTERFACE:\${CMAKE_CURRENT_LIST_DIR}/../../include>
    \$<INSTALL_INTERFACE:include>
)
add_library(Maxtest::Maxtest ALIAS maxtest)

function(maxtest_add_executable TARGET_NAME)
    add_executable(\${TARGET_NAME} \${ARGN})
    target_link_libraries(\${TARGET_NAME} PRIVATE Maxtest::Maxtest)
endfunction()

function(maxtest_add_test TARGET_NAME TEST_NAME)
    add_test(NAME \${TEST_NAME} COMMAND \${TARGET_NAME} \${TEST_NAME} \${ARGN})
endfunction()

include(CTest)
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE ON)
")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage"
     DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
