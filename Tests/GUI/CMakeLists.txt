cmake_minimum_required(VERSION 2.8)
project(rtype)

if($ENV{PROJECT})
    set(WD ../../)
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

file(GLOB TEST_SOURCE "${WD}Tests/GUI/*.cpp")

include_directories(${WD}include)
link_directories(../../Dependencies/SFML/Linux/lib)

#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
add_executable(gui ${TEST_SOURCE})

target_link_libraries(gui  ${PROJECT_SOURCE_DIR}/${WD}lib/libSaltyEngine.a ${PROJECT_SOURCE_DIR}/${WD}lib/libParser.so ${PROJECT_SOURCE_DIR}/${WD}lib/libSFMLSaltyEngine.so -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -lpthread -ldl)