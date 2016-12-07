cmake_minimum_required(VERSION 3.6)
project(rtype)

find_package(PkgConfig)

pkg_check_modules(SFML sfml-all)

#if($ENV{PROJECT})
    set(WD ../../)
#endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

file(GLOB SOURCE_TEST_ADRIEN_FILE "${WD}Tests/Adrien/*.cpp")

include_directories(${WD}include)

add_executable(test_adrien ${SOURCE_TEST_ADRIEN_FILE})

target_link_libraries(test_adrien ${PROJECT_SOURCE_DIR}/${WD}lib/libSaltyEngine.a ${PROJECT_SOURCE_DIR}/${WD}lib/libSFMLSaltyEngine.so -lpthread -ldl ${SFML_LIBRARIES})