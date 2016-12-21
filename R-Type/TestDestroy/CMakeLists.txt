cmake_minimum_required(VERSION 3.6)
project(TestDestroy)

include_directories(../../include)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

link_directories(../../lib)

add_executable(TestDestroy ${SOURCE_FILES})

target_link_libraries(TestDestroy
        -lSaltyEngine
        -lSFMLSaltyEngine
        -lParser
        -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)