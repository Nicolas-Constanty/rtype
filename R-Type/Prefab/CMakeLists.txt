cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -rdynamic")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Metas)

include_directories("include" "Dependencies/SFML/Linux/include")

# MONSTER
file(GLOB MONSTER_SOURCE_FILE "src/Prefabs/Monster/*.cpp")
add_library(monster SHARED ${MONSTER_SOURCE_FILE})
target_link_libraries(monster ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# MISSILE MEDUSA
file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Prefabs/Missile/MissileMedusa/*.cpp" "src/Prefabs/Missile/*.cpp")
add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
target_link_libraries(missile_medusa ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# MISSILE LASER
file(GLOB MISSILE_LASER_SOURCE_FILE "src/Prefabs/Missile/Laser/*.cpp")
add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
target_link_libraries(missile_laser ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# DEFAULT ENEMY BULLET
file(GLOB MISSILE_ENEMY_BULLET "src/Prefabs/Missile/EnemyBullet/*.cpp")
add_library(missile_enemy_bullet SHARED ${MISSILE_ENEMY_BULLET})
target_link_libraries(missile_enemy_bullet ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# MATE (network managed client)
file(GLOB MATE_SOURCE_FILES "src/Prefabs/Mate/*.cpp")
file(GLOB MATE_INC_FILES "include/Prefabs/Mate/*.hpp")
add_library(mate SHARED ${MATE_SOURCE_FILES} ${MATE_INC_FILES})
target_link_libraries(mate ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# PLAYER
file(GLOB PLAYER_SOURCE_FILE "src/Prefabs/Player/*.cpp" "src/Rtype/Game/Client/*.cpp" "src/Rtype/Game/Common/*.cpp" "src/Protocol/Game/*.cpp")
file(GLOB PLAYER_INC_FILE "include/Prefabs/Player/*.hpp")
add_library(player SHARED ${PLAYER_SOURCE_FILE} ${PLAYER_INC_FILE})
target_link_libraries(player ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

# WALKING MONSTER
file(GLOB WALKINGMONSTER_SOURCE_FILE "src/Prefabs/MonsterWalker/*.cpp")
add_library(monster_walker SHARED ${WALKINGMONSTER_SOURCE_FILE})
target_link_libraries(monster_walker ${PROJECT_SOURCE_DIR}/lib/libSaltyEngine.so ${PROJECT_SOURCE_DIR}/lib/libnetwork.so -ldl)

add_dependencies(player SFMLSaltyEngine network)
add_dependencies(mate SFMLSaltyEngine network)
add_dependencies(missile_medusa SFMLSaltyEngine network)
add_dependencies(monster SFMLSaltyEngine network)
add_dependencies(missile_laser SFMLSaltyEngine network)
add_dependencies(monster_walker SFMLSaltyEngine network)
add_dependencies(missile_enemy_bullet SFMLSaltyEngine network)
add_custom_target(prefabs DEPENDS player mate missile_medusa monster missile_laser monster_walker missile_enemy_bullet)