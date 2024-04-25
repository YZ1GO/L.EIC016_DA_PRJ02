cmake_minimum_required(VERSION 3.27)
project(feup_da_02)

set(CMAKE_CXX_STANDARD 14)
#file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(feup_da_02
        main.cpp
        include/Graph.h
        include/MutablePriorityQueue.h
        include/Utilities.h             src/Utilities.cpp
        include/Location.h              src/Location.cpp
)
