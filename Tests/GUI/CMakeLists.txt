cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

file(GLOB TEST_SOURCE "Tests/GUI/*.cpp")

include_directories(include)
link_directories(../../lib)

#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
add_executable(gui ${TEST_SOURCE})

target_link_libraries(gui lSaltyEngine lSFMLSaltyEngine lParser lpthread ldl lsfml-system lsfml-window lsfml-graphics lsfml-audio)
