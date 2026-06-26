cmake_minimum_required(VERSION 3.16)                  # Minimum version of CMake

project(ShortestPathEngine VERSION 1.0 LANGUAGES CXX) # Project name

set(CMAKE_CXX_STANDARD 17)                            # Compile using C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ShortestPathEngine                    # Creates executables

    # List of source files to be compiled
    src/main.cpp
    src/WeightedGraph.cpp
    src/Dijkstra.cpp
)

# Whenever you see, look inside include
target_include_directories(
    ShortestPathEngine 
    PRIVATE 
    include
)