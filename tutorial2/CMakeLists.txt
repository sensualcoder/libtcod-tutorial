include_directories(/usr/local/include/libtcod)
include_directories(include)

set(SOURCES src/tutorial2.cpp src/Actor.cpp src/Map.cpp src/Engine.cpp)

add_executable(tutorial2 ${SOURCES})