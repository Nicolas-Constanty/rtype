cmake_minimum_required(VERSION 2.8)
project(rtype)

if($ENV{PROJECT})
    set(WD ../../)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

file(GLOB SOURCE_TEST_ADRIEN_FILE "${WD}Tests/Adrien/*.cpp")

include_directories(${WD}include)

add_executable(test_adrien ${SOURCE_TEST_ADRIEN_FILE})

target_link_libraries(test_adrien ${PROJECT_SOURCE_DIR}/${WD}lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/${WD}lib/libSFMLSaltyEngine.so -lpthread -ldl ${SFML_LIBRARIES} -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio)# -Wl,-rpath=$(PROJECT_DIR)/Dependencies/SFML/Linux/lib)