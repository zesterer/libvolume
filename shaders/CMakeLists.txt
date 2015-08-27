#######################
#### CONFIGURATION ####
#######################

#Shaders
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/std-vertex-shader.glsl" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/std-fragment-shader.glsl" COPYONLY)

########################
#### Subdirectories ####
########################

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
PARENT_SCOPE
)
