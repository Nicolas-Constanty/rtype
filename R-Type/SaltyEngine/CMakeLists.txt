cmake_minimum_required(VERSION 3.6)
project(SaltyEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

#SET(WD ../../)

file(GLOB SOURCE_SALTYENGINE_FILE
        "${WD}src/SaltyEngine/*.cpp"
        "${WD}src/SaltyEngine/GUI/*.cpp"
        "${WD}src/SaltyEngine/Input/*.cpp"
        )

file(GLOB INCLUDE_SALTYENGINE_FILE
        "${WD}include/SaltyEngine/*.hpp"
        "${WD}include/SaltyEngine/GUI/*.hpp"
        "${WD}include/SaltyEngine/Input/*.hpp"
        )

include_directories("${WD}include")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_library(SaltyEngine STATIC ${SOURCE_SALTYENGINE_FILE})
target_link_libraries(SaltyEngine -ldl)