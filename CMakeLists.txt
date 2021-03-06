cmake_minimum_required(VERSION 3.11)
project(DSMCpp)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

# C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall")
endif()

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



FetchContent_Declare(mt
    GIT_REPOSITORY https://github.com/cslarsen/mersenne-twister.git
)

FetchContent_GetProperties(mt)
if(NOT mt_POPULATED)
  FetchContent_MakeAvailable(mt)
endif()

# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(DSMCpp PUBLIC OpenMP::OpenMP_CXX)
# endif()

# add the executable
add_executable(DSMCpp    
src/DSMCpp.cpp        
src/bound.cpp      
src/bound.h        
src/coll.cpp       
src/coll.h         
src/const.h        
src/io.cpp         
src/io.h           
src/llist.h        
src/log.cpp        
src/log.h          
src/matrix.h       
src/mesh.cpp       
src/mesh.h         
src/num.h          
src/par.h                
src/rand.h         
src/simulation.cpp 
src/simulation.h   
src/species.cpp    
src/species.h    
${mt_SOURCE_DIR}/mersenne-twister.cpp  
)

target_link_libraries(DSMCpp PRIVATE 
  nlohmann_json::nlohmann_json 
)

target_include_directories(DSMCpp PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/src"
"${libnpy_SOURCE_DIR}"
"${mt_SOURCE_DIR}"
)

add_compile_definitions(DEFAULT_CONFIG_PATH="../config.json")
add_compile_definitions(NPY_OUTPUT)