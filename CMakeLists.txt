cmake_minimum_required(VERSION 3.11)
project(DSMCpp)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -march=native -Wall")

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
    src/io.cpp

)

FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
    GIT_TAG v3.9.1
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_MakeAvailable(json)
endif()

FetchContent_Declare(libnpy
    GIT_REPOSITORY https://github.com/llohse/libnpy.git
)

FetchContent_GetProperties(libnpy)
if(NOT libnpy_POPULATED)
  FetchContent_MakeAvailable(libnpy)
endif()

target_link_libraries(DSMCpp PRIVATE 
                      nlohmann_json::nlohmann_json 
                      )

target_include_directories(DSMCpp PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           "${libnpy_SOURCE_DIR}"
                           )