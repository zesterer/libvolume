#######################
#### CONFIGURATION ####
#######################

#settings.h header file
configure_file(
"settings.h.in"
"settings.h"
)

#################
#### SOURCES ####
#################

#Add the appropriate source directories
set(LIBVOLUME_SOURCE_DIRS
${LIBVOLUME_SOURCE_DIRS}
"${PROJECT_BINARY_DIR}/src"
"${CMAKE_CURRENT_SOURCE_DIR}/"
"${CMAKE_CURRENT_SOURCE_DIR}/data/"
PARENT_SCOPE
)

#Add the appropriate source files
set(LIBVOLUME_SOURCE_FILES
${LIBVOLUME_SOURCE_FILES}
${CMAKE_CURRENT_SOURCE_DIR}/data/voxel.cpp
PARENT_SCOPE
)
