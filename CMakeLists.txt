cmake_minimum_required(VERSION 3.6)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILE "src/SaltyEngine/*.cpp" "include/SaltyEngine/*.hpp" "src/Common/*.cpp")
include_directories("include" "include/Common")

set(SOURCE_FILES INCLUDE_SRC)
add_executable(rtype ${SOURCE_FILE} ${INCLUDE_FILE} )