cmake_minimum_required(VERSION 3.10)
project(mod_fs_monitor)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find FreeSwitch
find_path(FREESWITCH_INCLUDE_DIR NAMES switch.h PATHS /usr/local/freeswitch/include/freeswitch)
find_library(FREESWITCH_LIBRARY NAMES freeswitch PATHS /usr/local/freeswitch/lib)

if(NOT FREESWITCH_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find FreeSwitch include directory")
endif()

if(NOT FREESWITCH_LIBRARY)
    message(FATAL_ERROR "Could not find FreeSwitch library")
endif()

# Find Qt5
find_package(Qt6 REQUIRED COMPONENTS Core)

# Set source files
set(SOURCES mod_fs_monitor.cpp)

# Include directories
include_directories(${FREESWITCH_INCLUDE_DIR})
include_directories(${Qt5Core_INCLUDE_DIRS})

# Link libraries
set(LIBS ${FREESWITCH_LIBRARY} Qt6::Core)

# Define the module
add_library(mod_fs_monitor MODULE ${SOURCES})

# Link the libraries
target_link_libraries(mod_fs_monitor ${LIBS})

set_target_properties(mod_fs_monitor PROPERTIES LINK_FLAGS "-static-libgcc -static-libstdc++")

# Installation path
install(TARGETS mod_fs_monitor DESTINATION /usr/local/freeswitch/mod)
