set(CMAKE_C_COMPILER /usr/bin/gcc)
cmake_minimum_required(VERSION 3.0)

project(Humilddleware C)

add_executable(main main.c notifcons.c notifengine.c srh.c submanager.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})