file(GLOB APPTEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

webframe_add_application(NAME apptest
    SOURCES ${APPTEST_SOURCES}
    INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    LINK_LIBRARIES Maxtest::Maxtest
    RUNTIME mock)

maxtest_add_test(apptest_mock webframe::noop_test)
maxtest_add_test(apptest_mock webframe::dispatch_error_test)
maxtest_add_test(apptest_mock webframe::empty_router_test)