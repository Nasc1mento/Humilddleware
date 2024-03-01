# Set the compiler
set(CMAKE_C_COMPILER /usr/bin/gcc)

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.0)

# Set the project name and language
project(Humilddleware C)

# Add your source files to the executable
add_executable(main main.c notifcons.c notifengine.c srh.c submanager.c)

# Include the current source directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Find and link against the netdb library
# find_library(NETDB_LIBRARY NAMES netdb)

# target_link_libraries(main ${NETDB_LIBRARY})