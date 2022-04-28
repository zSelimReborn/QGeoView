cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(QGeoView LANGUAGES C CXX)

include(ExternalProject)

# Set the external install location
if(NOT EXTERNAL_INSTALL_LOCATION)
    set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
endif()

#set(USE_GDAL_FEATURES ON)

# Add to the includes
include_directories(SYSTEM ${EXTERNAL_INSTALL_LOCATION}/include)

# Add to the libraries
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_subdirectory(demo)
add_subdirectory(lib)
