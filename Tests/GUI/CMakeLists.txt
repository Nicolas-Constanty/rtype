cmake_minimum_required(VERSION 2.8)
project(rtype)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

file(GLOB TEST_SOURCE "Tests/GUI/*.cpp")

include_directories(include)

#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
add_executable(gui ${TEST_SOURCE})

target_link_libraries(gui
        ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so
        ${PROJECT_SOURCE_DIR}/lib/libSFMLSaltyEngine.so
        ${PROJECT_SOURCE_DIR}/${WD}lib/libParser.so
        -lpthread -ldl -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)