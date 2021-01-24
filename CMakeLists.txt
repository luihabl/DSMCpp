cmake_minimum_required(VERSION 3.10)
project(DSMCpp)

# C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall")

# add the executable
add_executable(DSMCpp 

    src/DSMCpp.cpp 
    src/log.cpp
    src/rand.cpp
    src/species.cpp
    src/simulation.cpp
    src/bound.cpp
    src/mesh.cpp
    src/coll.cpp

)

target_include_directories(DSMCpp PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )