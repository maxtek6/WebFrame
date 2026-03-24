# CEF distributes a prebuilt shared library (libcef) plus wrapper source code
# (libcef_dll_wrapper) that must be compiled. This port downloads the official
# CEF binary distribution, builds the wrapper, and installs everything.

set(CEF_VERSION "122.1.10+gc902316+chromium-122.0.6261.112")

# ---------------------------------------------------------------------------
# Platform-specific archive selection (non-Windows only)
# ---------------------------------------------------------------------------
if(VCPKG_TARGET_IS_LINUX)
    set(CEF_PLATFORM "linux64")
elseif(VCPKG_TARGET_IS_OSX)
    if(VCPKG_TARGET_ARCHITECTURE STREQUAL "arm64")
        set(CEF_PLATFORM "macosarm64")
    else()
        set(CEF_PLATFORM "macosx64")
    endif()
else()
    message(FATAL_ERROR "CEF: unsupported platform")
endif()

set(CEF_ARCHIVE "cef_binary_${CEF_VERSION}_${CEF_PLATFORM}_minimal.tar.bz2")

vcpkg_download_distfile(ARCHIVE
    URLS "https://cef-builds.spotifycdn.com/${CEF_ARCHIVE}"
    FILENAME "${CEF_ARCHIVE}"
    # After the first download attempt vcpkg will print the real SHA512.
    # Replace the placeholder "0" hashes above with the correct values.
    SKIP_SHA512
)

vcpkg_extract_source_archive(SOURCE_PATH ARCHIVE "${ARCHIVE}")

# ---------------------------------------------------------------------------
# Build libcef_dll_wrapper (static library compiled from source)
# ---------------------------------------------------------------------------
file(COPY "${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt" DESTINATION "${SOURCE_PATH}")

vcpkg_cmake_configure(SOURCE_PATH "${SOURCE_PATH}")
vcpkg_cmake_install()

# ---------------------------------------------------------------------------
# Install prebuilt CEF shared library and helpers
# ---------------------------------------------------------------------------
if(VCPKG_TARGET_IS_LINUX)
    file(INSTALL "${SOURCE_PATH}/Release/libcef.so" DESTINATION "${CURRENT_PACKAGES_DIR}/lib")
    # Also install EGL/GLES/Vulkan helper libraries if present
    file(GLOB _cef_helpers "${SOURCE_PATH}/Release/libEGL.so" "${SOURCE_PATH}/Release/libGLESv2.so"
         "${SOURCE_PATH}/Release/libvk_swiftshader.so" "${SOURCE_PATH}/Release/libvulkan.so.1")
    if(_cef_helpers)
        file(INSTALL ${_cef_helpers} DESTINATION "${CURRENT_PACKAGES_DIR}/lib")
    endif()
    # Install v8 snapshot and sandbox helper
    file(GLOB _cef_data "${SOURCE_PATH}/Release/*.bin" "${SOURCE_PATH}/Release/chrome-sandbox")
    if(_cef_data)
        file(INSTALL ${_cef_data} DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/bin")
    endif()
elseif(VCPKG_TARGET_IS_OSX)
    file(GLOB _cef_framework "${SOURCE_PATH}/Release/Chromium Embedded Framework.framework")
    if(_cef_framework)
        file(INSTALL ${_cef_framework} DESTINATION "${CURRENT_PACKAGES_DIR}/lib")
    endif()
endif()

# Tell vcpkg that this port intentionally provides shared libraries even if
# the triplet default is static (CEF is always a shared library).
set(VCPKG_POLICY_DLLS_WITHOUT_EXPORTS enabled)

# ---------------------------------------------------------------------------
# Install CEF headers
# ---------------------------------------------------------------------------
file(INSTALL "${SOURCE_PATH}/include/" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

# ---------------------------------------------------------------------------
# Install resource files (PAK, locales, ICU data, etc.)
# ---------------------------------------------------------------------------
if(EXISTS "${SOURCE_PATH}/Resources")
    file(INSTALL "${SOURCE_PATH}/Resources/" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/Resources")
endif()

# ---------------------------------------------------------------------------
# Install CMake config
# ---------------------------------------------------------------------------
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/cef-config.cmake"
     DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")

# ---------------------------------------------------------------------------
# Copyright
# ---------------------------------------------------------------------------
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE.txt")

# ---------------------------------------------------------------------------
# Usage hint
# ---------------------------------------------------------------------------
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage"
     DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
