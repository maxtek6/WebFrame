function(webframe_add_runtime)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs
        SOURCES
        PRIVATE_INCLUDE_DIRS
        PUBLIC_INCLUDE_DIRS
        PRIVATE_LINK_LIBRARIES
        PUBLIC_LINK_LIBRARIES)
    cmake_parse_arguments(RUNTIME
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )
    add_library(webframe_${RUNTIME_NAME} STATIC ${RUNTIME_SOURCES})
    if(RUNTIME_PRIVATE_INCLUDE_DIRS)
        target_include_directories(webframe_${RUNTIME_NAME} PRIVATE ${RUNTIME_PRIVATE_INCLUDE_DIRS})
    endif()
    if(RUNTIME_PUBLIC_INCLUDE_DIRS)
        target_include_directories(webframe_${RUNTIME_NAME} PUBLIC ${RUNTIME_PUBLIC_INCLUDE_DIRS})
    endif()
    if(RUNTIME_PRIVATE_LINK_LIBRARIES)
        target_link_libraries(webframe_${RUNTIME_NAME} PRIVATE ${RUNTIME_PRIVATE_LINK_LIBRARIES})
    endif()
    if(RUNTIME_PUBLIC_LINK_LIBRARIES)
        target_link_libraries(webframe_${RUNTIME_NAME} PUBLIC ${RUNTIME_PUBLIC_LINK_LIBRARIES})
    endif()
endfunction()

function(webframe_add_application)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs
        SOURCES
        PRIVATE_INCLUDE_DIRS
        PUBLIC_INCLUDE_DIRS
        PRIVATE_LINK_LIBRARIES
        PUBLIC_LINK_LIBRARIES
        RUNTIME)
    cmake_parse_arguments(APPLICATION
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN})
endfunction()