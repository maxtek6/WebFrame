vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO maxtek6/hyperpage
    REF b679d32305783aff6cc37600387616c48e8f07ff
    SHA512 9cc0187583522afe070e9cee2fecb73594ee2348c47b733fc73bb4187ab9dd7cd1ebaeb2ab122ebd1a93b04a739e5c6792bd0f9a99cc0539e46920346b71072e
    HEAD_REF master
    PATCHES
        fix-missing-cstdint.patch
)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(
    PACKAGE_NAME hyperpage
    CONFIG_PATH lib/cmake/hyperpage
)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_copy_tools(TOOL_NAMES hyperpack AUTO_CLEAN)

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage"
     DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
