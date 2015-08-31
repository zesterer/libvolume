#######################
#### CONFIGURATION ####
#######################

########################
#### Subdirectories ####
########################

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/physics")

#################
#### SOURCES ####
#################

#Add the appropriate source directories
set(LIBVOLUME_SOURCE_DIRS
${LIBVOLUME_SOURCE_DIRS}
"${CMAKE_CURRENT_SOURCE_DIR}"
PARENT_SCOPE
)

#Add the appropriate source files
set(LIBVOLUME_SOURCE_FILES
${LIBVOLUME_SOURCE_FILES}
${CMAKE_CURRENT_SOURCE_DIR}/entity.cpp
${CMAKE_CURRENT_SOURCE_DIR}/realm.cpp
${CMAKE_CURRENT_SOURCE_DIR}/actor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/voxelactor.cpp
PARENT_SCOPE
)
