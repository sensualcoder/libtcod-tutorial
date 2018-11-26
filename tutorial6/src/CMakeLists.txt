add_subdirectory(Components)

set(SOURCES Entity.cpp 
            Map.cpp 
            Engine.cpp
            Subject.cpp)

add_library(src ${SOURCES})
target_link_libraries(src Components)