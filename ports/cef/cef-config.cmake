# CMake config file for the CEF vcpkg overlay port.
#
# Provides the following imported targets:
#   CEF::wrapper  – static libcef_dll_wrapper (compiled from source)
#   CEF::lib      – prebuilt libcef_static static library
#   CEF::CEF      – convenience interface that links both
#
# Variables:
#   CEF_RESOURCE_DIR – path to the CEF Resources directory (PAK/locale files)

get_filename_component(_CEF_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

# ---------- CEF::wrapper (static) ----------
if(NOT TARGET CEF::wrapper)
    add_library(CEF::wrapper STATIC IMPORTED)

    find_library(_CEF_WRAPPER_RELEASE
        NAMES cef_dll_wrapper
        PATHS "${_CEF_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    find_library(_CEF_WRAPPER_DEBUG
        NAMES cef_dll_wrapper
        PATHS "${_CEF_ROOT}/debug/lib"
        NO_DEFAULT_PATH
    )

    if(_CEF_WRAPPER_RELEASE)
        set_property(TARGET CEF::wrapper APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(CEF::wrapper PROPERTIES
            IMPORTED_LOCATION_RELEASE "${_CEF_WRAPPER_RELEASE}"
        )
    endif()
    if(_CEF_WRAPPER_DEBUG)
        set_property(TARGET CEF::wrapper APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(CEF::wrapper PROPERTIES
            IMPORTED_LOCATION_DEBUG "${_CEF_WRAPPER_DEBUG}"
        )
    endif()

    set_target_properties(CEF::wrapper PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${_CEF_ROOT}/include"
    )
endif()

# ---------- CEF::lib (prebuilt static) ----------
if(NOT TARGET CEF::lib)
    add_library(CEF::lib STATIC IMPORTED)

    find_library(_CEF_STATIC_RELEASE
        NAMES cef_static
        PATHS "${_CEF_ROOT}/lib"
        NO_DEFAULT_PATH
    )
    find_library(_CEF_STATIC_DEBUG
        NAMES cef_static
        PATHS "${_CEF_ROOT}/debug/lib"
        NO_DEFAULT_PATH
    )

    if(_CEF_STATIC_RELEASE)
        set_property(TARGET CEF::lib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
        set_target_properties(CEF::lib PROPERTIES
            IMPORTED_LOCATION_RELEASE "${_CEF_STATIC_RELEASE}"
        )
    endif()
    if(_CEF_STATIC_DEBUG)
        set_property(TARGET CEF::lib APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
        set_target_properties(CEF::lib PROPERTIES
            IMPORTED_LOCATION_DEBUG "${_CEF_STATIC_DEBUG}"
        )
    endif()
endif()

# ---------- CEF::CEF (convenience) ----------
if(NOT TARGET CEF::CEF)
    add_library(CEF::CEF INTERFACE IMPORTED)
    set_property(TARGET CEF::CEF PROPERTY
        INTERFACE_LINK_LIBRARIES CEF::wrapper CEF::lib
    )
endif()

# ---------- Resources ----------
set(CEF_RESOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Resources" CACHE PATH "CEF resource directory")

# ---------- Validation ----------
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CEF DEFAULT_MSG
    _CEF_WRAPPER_RELEASE
)
