cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")


file(GLOB SOURCE_SALTYENGINE_SFML_FILE "src/SaltyEngine/SFML/*.cpp")

file(GLOB INCLUDE_SALTYENGINE_SFML_FILE "include/SaltyEngine/SFML/*.hpp")

include_directories(include)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(SFMLSaltyEngine SHARED ${SOURCE_SALTYENGINE_SFML_FILE})
target_link_libraries(SFMLSaltyEngine ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a)

add_custom_target(BUILD_ENGINE DEPENDS SaltyEngine SFMLSaltyEngine)