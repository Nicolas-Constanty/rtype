cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -rdynamic")

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Metas)

include_directories("include" "Dependencies/SFML/Linux/include")

# MONSTER
file(GLOB MONSTER_SOURCE_FILE "src/Prefabs/Monster/*.cpp")
add_library(monster SHARED ${MONSTER_SOURCE_FILE})
target_link_libraries(monster ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# MISSILE MEDUSA
file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Prefabs/Missile/MissileMedusa/*.cpp" "src/Prefabs/Missile/*.cpp")
add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
target_link_libraries(missile_medusa ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# MISSILE LASER
file(GLOB MISSILE_LASER_SOURCE_FILE "src/Prefabs/Missile/Laser/*.cpp")
add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
target_link_libraries(missile_laser ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)


# MATE (network managed client)
file(GLOB MATE_SOURCE_FILES "src/Prefabs/Mate/*.cpp")
file(GLOB MATE_INC_FILES "include/Prefabs/Mate/*.hpp")
add_library(mate SHARED ${MATE_SOURCE_FILES} ${MATE_INC_FILES})
target_link_libraries(mate ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)

# PLAYER
file(GLOB PLAYER_SOURCE_FILE "src/Prefabs/Player/*.cpp")
file(GLOB PLAYER_INC_FILE "include/Prefabs/Player/*.hpp")
add_library(player SHARED ${PLAYER_SOURCE_FILE} ${PLAYER_INC_FILE})
target_link_libraries(player ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.a -ldl)
