################
#### INITIAL####
################

#Make sure we have a minimum version
cmake_minimum_required(VERSION 2.6)

###############
#### SETUP ####
###############

#Set globally required variables
set(LIBVOLUME_NAME libvolume)
set(LIBVOLUME_LINK_LIBRARIES)

#Should the application library be statically compiled?
option(LIBVOLUME_COMPILE_STATIC "Compile the library statically" TRUE)

#Set the project name and primary language
project(${LIBVOLUME_NAME} CXX)

#Set the C++ standard for the library (variable templates and other features)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set the version numbers
set(LIBVOLUME_VERSION_MAJOR 0)
set(LIBVOLUME_VERSION_MINOR 0)
set(LIBVOLUME_VERSION_BUILD 0)
set(LIBVOLUME_VERSION "${LIBVOLUME_VERSION_MAJOR}.${LIBVOLUME_VERSION_MINOR}.${LIBVOLUME_VERSION_BUILD}")

#Set CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})

#Set the source files and directories we will use
set(LIBVOLUME_SOURCE_FILES)
set(LIBVOLUME_SOURCE_DIRS)

#######################
#### ADD LIBRARIES ####
#######################

########
# SFML #
########

#Find SFML
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	set(LIBVOLUME_LINK_LIBRARIES ${LIBVOLUME_LINK_LIBRARIES} ${SFML_LIBRARIES})
else ()
	message("SFML could not be found, and is required to build this library.")
endif ()

#######
# GLM #
#######

#Find GLM
find_package(GLM REQUIRED)

if (GLM_FOUND)
	include_directories(${GLM_INCLUDE_DIR})
else ()
	message("GLM could not be found, and is required to build this library.")
endif ()

#############
# GLBINDING #
#############

#Find GLM
find_package(GLBINDING REQUIRED)

if (GLBINDING_FOUND)
	include_directories(${GLBINDING_INCLUDE_DIR})
	set(LIBVOLUME_LINK_LIBRARIES ${LIBVOLUME_LINK_LIBRARIES} ${GLBINDING_LIBRARIES})
else ()
	message("GLBINDING could not be found, and is required to build this library.")
endif ()

##################
#### BUILDING ####
##################

#Include the src directory (all the project code)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src")

#Add all directories that need to be added
include_directories(${LIBVOLUME_SOURCE_DIRS})

#Build the application library
if (LIBVOLUME_COMPILE_STATIC)
	add_library(${LIBVOLUME_NAME} STATIC ${LIBVOLUME_SOURCE_FILES})
else ()
	add_library(${LIBVOLUME_NAME} SHARED ${LIBVOLUME_SOURCE_FILES})
endif ()

#Link all the libraries with the application library
target_link_libraries(${LIBVOLUME_NAME} ${LIBVOLUME_LINK_LIBRARIES})

######################
#### INSTALLATION ####
######################

#Installation options
#install(
#TARGETS
#	${LIBVOLUME_NAME}
#RUNTIME DESTINATION ${BIN_INSTALL_DIR}
#LIBRARY DESTINATION ${LIB_INSTALL_DIR}
#ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
#FILES
#	${LIBVOLUME_SOURCE_FILES} DESTINATION ${INCLUDE_INSTALL_DIR}
#COMPONENT libraries
#)
