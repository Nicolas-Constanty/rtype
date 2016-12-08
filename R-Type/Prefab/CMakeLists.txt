cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Metas)

include_directories("include" "Dependencies/SFML/Linux/include")

# MONSTER
file(GLOB MONSTER_SOURCE_FILE "src/Monster/*.cpp")
add_library(monster SHARED ${MONSTER_SOURCE_FILE})
target_link_libraries(monster ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# MISSILE MEDUSA
file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Missile/MissileMedusa/*.cpp" "src/Missile/*.cpp")
add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
target_link_libraries(missile_medusa ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# MISSILE LASER
file(GLOB MISSILE_LASER_SOURCE_FILE "src/Missile/Laser/*.cpp" "src/Missile/*.cpp")
add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
target_link_libraries(missile_laser ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# PLAYER
file(GLOB PLAYER_SOURCE_FILE "src/Player/*.cpp")
add_library(player SHARED ${PLAYER_SOURCE_FILE})
target_link_libraries(player ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)