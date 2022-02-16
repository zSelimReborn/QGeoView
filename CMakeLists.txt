cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(QGeoView LANGUAGES C CXX)

include(ExternalProject)

# Set the external install location
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

if(NOT LIB_INSTALL_LOCATION)
    set(LIB_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
endif()

# Add to the includes
include_directories(SYSTEM ${EXTERNAL_INSTALL_LOCATION}/include)

# Add to the libraries
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

add_subdirectory(demo)
add_subdirectory(lib)
