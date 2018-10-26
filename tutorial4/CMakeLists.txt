project(Tutorial4)

include_directories(/usr/local/include/libtcod)
include_directories(include)

set(SOURCES src/main.cpp 
            src/Actor.cpp 
            src/Map.cpp 
            src/Engine.cpp)

add_executable(tutorial4 ${SOURCES})