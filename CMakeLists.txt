
# This version is just the major.minor that was on my system at the time of writing
cmake_minimum_required(VERSION 3.12)
# Name of the CMake project
project(LibtcodTutorials)

## Find and link libtcod
# Specify the /usr/local/lib directory if install from source
link_directories(/usr/local/lib)
# Link the actual library
link_libraries(tcod)

## Add the subdirectories containing the tutorials
add_subdirectory(tutorial1)
add_subdirectory(tutorial2)

include_directories(${PROJECT_SOURCE_DIR}/tutorial3/include)
add_subdirectory(tutorial3)
