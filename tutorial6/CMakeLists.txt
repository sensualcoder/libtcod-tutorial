project(Tutorial6)

include_directories(/usr/local/include/libtcod)
include_directories(include)

add_subdirectory(src)

set(SOURCES main.cpp)

add_executable(tutorial6 ${SOURCES})
target_link_libraries(tutorial6 src)