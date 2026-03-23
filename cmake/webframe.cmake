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
        INCLUDE_DIRS
        LINK_LIBRARIES
        RUNTIME)
    cmake_parse_arguments(APPLICATION
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN})
    foreach(RUNTIME ${APPLICATION_RUNTIME})
        set(TARGET_NAME ${APPLICATION_NAME}_${RUNTIME})
        if(WIN32)
            if(RUNTIME STREQUAL "desktop")
                add_executable(${TARGET_NAME} WIN32 ${APPLICATION_SOURCES})
            else()
                add_executable(${TARGET_NAME} ${APPLICATION_SOURCES})
            endif()
        else()
            add_executable(${TARGET_NAME} ${APPLICATION_SOURCES})
        endif()
        if(APPLICATION_INCLUDE_DIRS)
            target_include_directories(${TARGET_NAME} PRIVATE ${APPLICATION_INCLUDE_DIRS})
        endif()
        target_link_libraries(${TARGET_NAME} PRIVATE webframe_${RUNTIME} ${APPLICATION_LINK_LIBRARIES})
        add_dependencies(${TARGET_NAME} webframe_${RUNTIME})
    endforeach()
endfunction()