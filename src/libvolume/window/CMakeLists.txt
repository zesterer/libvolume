#######################
#### CONFIGURATION ####
#######################

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
${CMAKE_CURRENT_SOURCE_DIR}/window.cpp
${CMAKE_CURRENT_SOURCE_DIR}/eventmanager.cpp
PARENT_SCOPE
)
