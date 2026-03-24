vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO kobbyowen/MegaMimes
    REF b839068db99cbfcff1af8df1229bd7e41701fe96
    SHA512 1581ddb6e85929ce7ec1e97578ad77fadd3f6ac82a1e4a379772dfa90b048a9c508059cc63525feef73a7a08e8553789830ef48e28ebc0e6a1123f1b0fb69889
    HEAD_REF master
)

# MegaMimes does not include a CMakeLists.txt, so provide one
file(COPY "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt" DESTINATION "${SOURCE_PATH}")

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(CONFIG_PATH share/cmake/megamimes)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
