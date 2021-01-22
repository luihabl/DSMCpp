cmake_minimum_required(VERSION 3.10)

# set the project name
project(DSMCpp)

# add the executable
add_executable(DSMCpp src/DSMCpp.cpp)

target_include_directories(DSMCpp PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )