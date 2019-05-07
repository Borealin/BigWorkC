cmake_minimum_required(VERSION 3.12)
project(BigWorkC C)

set(CMAKE_C_STANDARD  99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

aux_source_directory(libgraphics DIR_LIB)
aux_source_directory(simpleGUI DIR_GUI)
aux_source_directory(Utils DIR_UTILS)
include_directories(include simpleGUI Utils)

add_executable(${PROJECT_NAME} ${DIR_LIB} ${DIR_GUI} ${DIR_UTILS} main.c)