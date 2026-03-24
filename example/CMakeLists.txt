
set(HYPERPAGE_ARCHIVE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(HYPERPAGE_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/hyperpage.db)

file(GLOB_RECURSE HYPERPAGE_FRONTEND_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/frontend/*)

add_custom_command(
    OUTPUT ${HYPERPAGE_ARCHIVE_PATH}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND hyperpage::hyperpack --output ${HYPERPAGE_ARCHIVE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/frontend
    DEPENDS ${HYPERPAGE_FRONTEND_SOURCES}
    COMMENT "Bundling example frontend with hyperpack"
    VERBATIM
)

add_custom_target(example_frontend_bundle ALL
    DEPENDS ${HYPERPAGE_ARCHIVE_PATH})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/archive.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/archive.hpp
    @ONLY
)
if(WIN32)
    webframe_add_application(NAME example
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
        LINK_LIBRARIES yyjson::yyjson hyperpage::hyperpage
        RUNTIME desktop server)
else()
    webframe_add_application(NAME example
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
        LINK_LIBRARIES yyjson::yyjson hyperpage::hyperpage
        RUNTIME server)
endif()