project(Tutorial6)

include_directories(/usr/local/include/libtcod)
include_directories(include)

set(SOURCES src/main.cpp 
            src/AI.cpp
            src/Entity.cpp 
            src/Map.cpp 
            src/Engine.cpp
            src/Subject.cpp)

add_executable(tutorial6 ${SOURCES})