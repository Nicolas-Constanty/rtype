cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../Assets/Metas)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -rdynamic")

	set(PREFAB_LIBRARIES SaltyEngine network ldl)
elseif(MSVC)

<<<<<<< Updated upstream
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Metas)

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
	
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES")

	set(PREFAB_LIBRARIES SaltyEngine SFMLSaltyEngine Network)
=======
	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
	
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DWIN32_LEAN_AND_MEAN")
>>>>>>> Stashed changes
endif()

include_directories("include")
link_directories(../../lib)
<<<<<<< Updated upstream


=======

set(PREFAB_LIBRARIES lSaltyEngine lnetwork ldl)
>>>>>>> Stashed changes

# MONSTER
file(GLOB MONSTER_SOURCE_FILE "src/Prefabs/Monster/*.cpp" "include/Prefabs/GenericController.hpp" "include/Prefabs/Monster/*.hpp" ${NETWORK})
add_library(monster SHARED ${MONSTER_SOURCE_FILE})
target_link_libraries(monster ${PREFAB_LIBRARIES})

# MISSILE MEDUSA
file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Prefabs/Missile/MissileMedusa/*.cpp" "src/Prefabs/Missile/*.cpp" "include/Prefabs/Missile/*.hpp" "include/Prefabs/Missile/MissileMedusa/*.hpp" ${NETWORK})
add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
target_link_libraries(missile_medusa ${PREFAB_LIBRARIES})

# MISSILE LASER
file(GLOB MISSILE_LASER_SOURCE_FILE "src/Prefabs/Missile/Laser/*.cpp" include/Prefabs/Missile/Laser/*.hpp)
add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
target_link_libraries(missile_laser ${PREFAB_LIBRARIES})

# DEFAULT ENEMY BULLET
file(GLOB MISSILE_ENEMY_BULLET "src/Prefabs/Missile/EnemyBullet/*.cpp" "include/Prefabs/Missile/EnemyBullet/*.hpp" ${NETWORK})
add_library(missile_enemy_bullet SHARED ${MISSILE_ENEMY_BULLET})
target_link_libraries(missile_enemy_bullet ${PREFAB_LIBRARIES})

# MATE (network managed client)
file(GLOB MATE_SOURCE_FILES "src/Prefabs/Mate/*.cpp")
file(GLOB MATE_INC_FILES "include/Prefabs/Mate/*.hpp")
add_library(mate SHARED ${MATE_SOURCE_FILES} ${MATE_INC_FILES})
target_link_libraries(mate ${PREFAB_LIBRARIES})

# PLAYER
file(GLOB PLAYER_SOURCE_FILE "src/Prefabs/Player/*.cpp" "src/Rtype/Game/Client/*.cpp" "src/Rtype/Game/Common/*.cpp" "src/Protocol/Game/*.cpp")
file(GLOB PLAYER_INC_FILE "include/Prefabs/Player/*.hpp")
add_library(player SHARED ${PLAYER_SOURCE_FILE} ${PLAYER_INC_FILE})
target_link_libraries(player ${PREFAB_LIBRARIES})

# WALKING MONSTER
file(GLOB WALKINGMONSTER_SOURCE_FILE "src/Prefabs/MonsterWalker/*.cpp" "include/Prefabs/MonsterWalker/*.hpp"  "src/Rtype/Game/Client/*.cpp" "src/Rtype/Game/Common/*.cpp" "src/Protocol/Game/*.cpp" "src/Rtype/Game/Server/*.cpp")
add_library(monster_walker SHARED ${WALKINGMONSTER_SOURCE_FILE})
target_link_libraries(monster_walker ${PREFAB_LIBRARIES})

# FLYING MONSTER
file(GLOB FLYINGMONSTER_SOURCE_FILE "src/Prefabs/MonsterFlying/*.cpp" "include/Prefabs/MonsterFlying/*.hpp")
add_library(monster_flying SHARED ${FLYINGMONSTER_SOURCE_FILE})
target_link_libraries(monster_flying ${PREFAB_LIBRARIES})

# BASIC EXPLOSION
file(GLOB EXPLOSIONBASIC_SOURCE_FILE "src/Prefabs/ExplosionBasic/*.cpp" include/Prefabs/ExplosionBasic/*.hpp)
add_library(explosion_basic SHARED ${EXPLOSIONBASIC_SOURCE_FILE})
target_link_libraries(explosion_basic ${PREFAB_LIBRARIES})

set(PREFAB_DEPENDENCIES SFMLSaltyEngine Network)

add_dependencies(player ${PREFAB_DEPENDENCIES})
add_dependencies(mate ${PREFAB_DEPENDENCIES})
add_dependencies(missile_medusa ${PREFAB_DEPENDENCIES})
add_dependencies(missile_laser ${PREFAB_DEPENDENCIES})
add_dependencies(explosion_basic ${PREFAB_DEPENDENCIES})
add_dependencies(missile_enemy_bullet ${PREFAB_DEPENDENCIES})
add_dependencies(monster ${PREFAB_DEPENDENCIES} missile_medusa)
add_dependencies(monster_walker ${PREFAB_DEPENDENCIES} missile_medusa missile_enemy_bullet explosion_basic)
add_dependencies(monster_flying ${PREFAB_DEPENDENCIES} missile_medusa missile_enemy_bullet explosion_basic)
set(PREFABS_TARGET player mate missile_medusa monster missile_laser monster_walker missile_enemy_bullet explosion_basic monster_flying)
add_custom_target(prefabs DEPENDS ${PREFABS_TARGET})