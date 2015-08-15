#Make sure we have a minimum version
cmake_minimum_required(VERSION 2.6)

#Set the project name
project(libvolume)

#The version number
set(LIBVOLUME_VERSION_MAJOR 0)
set(LIBVOLUME_VERSION_MINOR 0)
set(LIBVOLUME_VERSION_BUILD 0)

#Include the src directory
include_directories("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)
