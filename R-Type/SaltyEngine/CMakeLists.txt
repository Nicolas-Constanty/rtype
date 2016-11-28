cmake_minimum_required(VERSION 3.6)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILE "src/SaltyEngine/*.cpp" "src/SaltyEngine/Input/*.cpp" "src/SFML/*.cpp")
file(GLOB INCLUDE_FILE "include/SaltyEngine/*.hpp" "include/SaltyEngine/Input/*.hpp" "include/SFML/*.hpp")
include_directories("include")

set(SOURCE_FILES INCLUDE_SRC)
add_executable(rtype ${SOURCE_FILE} ${INCLUDE_FILE} include/SaltyEngine/Input.hpp)