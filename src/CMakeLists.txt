file(GLOB WEBFRAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(WEBFRAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(BUILD_RUNTIME)
    if(WIN32)
        file(GLOB WEBFRAME_DESKTOP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/desktop/*.cpp)
        webframe_add_runtime(NAME desktop
            SOURCES ${WEBFRAME_SOURCES} ${WEBFRAME_DESKTOP_SOURCES}
            PUBLIC_INCLUDE_DIRS ${WEBFRAME_INCLUDE_DIR} 
            PRIVATE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/desktop
            PUBLIC_LINK_LIBRARIES wx::core wx::webview)
        target_compile_definitions(webframe_desktop PUBLIC WEBFRAME_DESKTOP_RUNTIME=1)
    endif()
    file(GLOB WEBFRAME_SERVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/server/*.cpp)
    webframe_add_runtime(NAME server
        SOURCES ${WEBFRAME_SOURCES} ${WEBFRAME_SERVER_SOURCES}
        PUBLIC_INCLUDE_DIRS ${WEBFRAME_INCLUDE_DIR} 
        PRIVATE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/server
        PUBLIC_LINK_LIBRARIES libevent::core libevent::extra)
endif()

if(BUILD_TESTING)
    file(GLOB WEBFRAME_MOCK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/mock/*.cpp)
    webframe_add_runtime(NAME mock
        SOURCES ${WEBFRAME_SOURCES} ${WEBFRAME_MOCK_SOURCES}
        PUBLIC_INCLUDE_DIRS ${WEBFRAME_INCLUDE_DIR} 
        PRIVATE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/mock)
endif()