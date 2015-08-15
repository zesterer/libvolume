#Make sure we have a minimum version
cmake_minimum_required(VERSION 2.6)

#settings.h header file
configure_file(
"${PROJECT_SOURCE_DIR}/src/settings.h.in"
"${PROJECT_BINARY_DIR}/src/settings.h"
)

#To find settings.h, we must add the binary directory
include_directories("${PROJECT_BINARY_DIR}/src")

#Which source files does it use?
set(SOURCE_FILES
"${PROJECT_SOURCE_DIR}/src/settings.h"
)

#Installation rules
install(FILES ${SOURCE_FILES} DESTINATION include)

#Add the library
add_library(${PROJECT_NAME} ${SOURCE_FILES})
