cmake_minimum_required(VERSION 2.8)
project(rtype)

if($ENV{PROJECT})
    set(WD ../../)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

file(GLOB TEST_SOURCE "${WD}Tests/GUI/*.cpp")

include_directories(${WD}include)

#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
add_executable(gui ${TEST_SOURCE})

target_link_libraries(gui ${PROJECT_SOURCE_DIR}/${WD}lib/libSaltyEngine.a ${PROJECT_SOURCE_DIR}/${WD}lib/libSFMLSaltyEngine.so ${PROJECT_SOURCE_DIR}/${WD}lib/libParser.so -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)