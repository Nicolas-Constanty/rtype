cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

file(GLOB SOURCE_SALTYENGINE_FILE
        "src/SaltyEngine/*.cpp"
        "src/SaltyEngine/GUI/*.cpp"
        "src/SaltyEngine/Input/*.cpp"
        "src/Common/LibLoader.cpp"
        )

file(GLOB INCLUDE_SALTYENGINE_FILE
        "include/SaltyEngine/*.hpp"
        "include/SaltyEngine/GUI/*.hpp"
        "include/SaltyEngine/Input/*.hpp"
        )

include_directories("include")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/)

add_library(SaltyEngine STATIC ${SOURCE_SALTYENGINE_FILE})
target_link_libraries(SaltyEngine)