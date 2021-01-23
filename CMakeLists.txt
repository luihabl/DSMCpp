cmake_minimum_required(VERSION 3.10)
project(DSMCpp)

# C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add the executable
add_executable(DSMCpp 

    src/DSMCpp.cpp 
    src/log.cpp
    src/rand.cpp
    src/species.cpp

)

target_include_directories(DSMCpp PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )