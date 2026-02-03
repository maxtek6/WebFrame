# WebFrame Library Sources

add_library(webframe SHARED
  webframe.cpp
)

target_include_directories(webframe PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
  $<INSTALL_INTERFACE:include>
)

# Installation
install(TARGETS webframe
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
)
