cmake_minimum_required(VERSION 3.6)
project(rtype)

#find_package(PkgConfig)

#pkg_check_modules(SFML sfml-all)

if($ENV{PROJECT})
    set(WD ../../)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

file(GLOB TEST_SOURCE "${WD}Tests/GUI/*.cpp")

include_directories(${WD}include)

add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

add_executable(gui ${TEST_SOURCE})

target_link_libraries(gui ${PROJECT_SOURCE_DIR}/${WD}lib/libSaltyEngine.a ${PROJECT_SOURCE_DIR}/${WD}lib/libSFMLSaltyEngine.so -lpthread -ldl ${SFML_LIBRARIES} -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)