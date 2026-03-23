file(GLOB WEBFRAME_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(WEBFRAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if(BUILD_RUNTIME)
    message(STATUS "Building desktop runtime")
    message(STATUS "Building browser runtime")
endif()

if(BUILD_TESTING)
    file(GLOB WEBFRAME_MOCK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/mock/*.cpp)
    webframe_add_runtime(NAME mock
        SOURCES ${WEBFRAME_SOURCES} ${WEBFRAME_MOCK_SOURCES}
        PUBLIC_INCLUDE_DIRS ${WEBFRAME_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/runtimes/mock)
endif()