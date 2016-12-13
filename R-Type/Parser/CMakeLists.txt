cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -fPIC")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

file(GLOB SOURCE_SALTYENGINE_SFML_FILE "src/Parser/*.cpp")

file(GLOB INCLUDE_SALTYENGINE_SFML_FILE "include/Parser/*.hpp")

include_directories(include)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(Parser SHARED ${SOURCE_SALTYENGINE_SFML_FILE})