cmake_minimum_required(VERSION 2.8)
project(rtype CXX)

include_directories("include")

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Assets/Metas)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -rdynamic")

	set(PREFAB_LIBRARIES SaltyEngine Network dl)

#Windows
elseif(MSVC)

	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
	
	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DWIN32_LEAN_AND_MEAN -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES")

	set(PREFAB_LIBRARIES SaltyEngine SFMLSaltyEngine Network PrefabCommunication)

endif()

set(SRC_COMMON src/Common/Debug.cpp)

file(GLOB SRC_COMMMUNICATION
		"src/Rtype/Game/Client/*.cpp"
		"src/Protocol/Game/Client/*.cpp"
		"src/Rtype/Game/Server/*.cpp"
		"src/Prefabs/Player/PlayerController.cpp"
		src/Prefabs/Mate/MateComponent.cpp
		include/Prefabs/Mate/MateComponent.hpp
		)

add_library(PrefabCommunication SHARED ${SRC_COMMON} ${SRC_COMMMUNICATION})

# BEAM
file(GLOB BEAM_SOURCE_FILE "src/Prefabs/Beam/*.cpp"  "include/Prefabs/Beam/*.hpp")
add_library(beam SHARED ${BEAM_SOURCE_FILE})
target_link_libraries(beam ${PREFAB_LIBRARIES})

# MISSILES

	# MISSILE MEDUSA
	file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Prefabs/Missile/MissileMedusa/*.cpp" "src/Prefabs/Missile/*.cpp" "include/Prefabs/Missile/*.hpp" "include/Prefabs/Missile/MissileMedusa/*.hpp")
	add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
	target_link_libraries(missile_medusa ${PREFAB_LIBRARIES})

	# MISSILE LASER
	file(GLOB MISSILE_LASER_SOURCE_FILE "src/Prefabs/Missile/Laser/*.cpp" include/Prefabs/Missile/Laser/*.hpp)
	add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
	target_link_libraries(missile_laser ${PREFAB_LIBRARIES})

	# DEFAULT ENEMY BULLET
	file(GLOB MISSILE_ENEMY_BULLET "src/Prefabs/Missile/EnemyBullet/*.cpp" "src/Prefabs/Missile/*.cpp" "include/Prefabs/Missile/EnemyBullet/*.hpp")
	add_library(missile_enemy_bullet SHARED ${MISSILE_ENEMY_BULLET})
	target_link_libraries(missile_enemy_bullet ${PREFAB_LIBRARIES})

	# BASIC EXPLOSION
	file(GLOB EXPLOSIONBASIC_SOURCE_FILE "src/Prefabs/ExplosionBasic/*.cpp" include/Prefabs/ExplosionBasic/*.hpp)
	add_library(explosion_basic SHARED ${EXPLOSIONBASIC_SOURCE_FILE})
	target_link_libraries(explosion_basic ${PREFAB_LIBRARIES})

# SPACESHIPS

	# PLAYER
	file(GLOB PLAYER_SOURCE_FILE "src/Prefabs/Player/*.cpp")
	file(GLOB PLAYER_INC_FILE "include/Prefabs/Player/*.hpp")
	add_library(player SHARED ${PLAYER_SOURCE_FILE} ${PLAYER_INC_FILE})
	target_link_libraries(player ${PREFAB_LIBRARIES} missile_laser)

	# MATE (network managed client)
	file(GLOB MATE_SOURCE_FILES "src/Prefabs/Mate/*.cpp" )
	file(GLOB MATE_INC_FILES "include/Prefabs/Mate/*.hpp")
	add_library(mate SHARED ${MATE_SOURCE_FILES} ${MATE_INC_FILES})
	target_link_libraries(mate ${PREFAB_LIBRARIES} missile_laser)

	# POD
	file(GLOB POD_SOURCE_FILES "src/Prefabs/Pod/*.cpp")
	file(GLOB POD_INC_FILES "include/Prefabs/Pod/*.hpp")
	add_library(pod SHARED ${POD_SOURCE_FILES} ${POD_INC_FILES})
	target_link_libraries(pod ${PREFAB_LIBRARIES})

# MONSTERS

	# BASIC
	file(GLOB MONSTER_SOURCE_FILE "src/Prefabs/Monster/*.cpp" "include/Prefabs/GenericController.hpp" "include/Prefabs/Monster/*.hpp")
	add_library(monster SHARED ${MONSTER_SOURCE_FILE})
	target_link_libraries(monster ${PREFAB_LIBRARIES} missile_medusa)

	# WALKER
	file(GLOB WALKINGMONSTER_SOURCE_FILE "src/Prefabs/MonsterWalker/*.cpp" "include/Prefabs/MonsterWalker/*.hpp")
	add_library(monster_walker SHARED ${WALKINGMONSTER_SOURCE_FILE})
	target_link_libraries(monster_walker ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

	# FLYING
	file(GLOB FLYINGMONSTER_SOURCE_FILE "src/Prefabs/MonsterFlying/*.cpp" "include/Prefabs/MonsterFlying/*.hpp")
	add_library(monster_flying SHARED ${FLYINGMONSTER_SOURCE_FILE})
	target_link_libraries(monster_flying ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic)

set(PREFAB_DEPENDENCIES SFMLSaltyEngine Network PrefabCommunication)

#BEAM
add_dependencies(beam ${PREFAB_DEPENDENCIES})

#Missiles
add_dependencies(missile_medusa ${PREFAB_DEPENDENCIES})
add_dependencies(missile_laser ${PREFAB_DEPENDENCIES})
add_dependencies(explosion_basic ${PREFAB_DEPENDENCIES})
add_dependencies(missile_enemy_bullet ${PREFAB_DEPENDENCIES})

#Monsters
add_dependencies(monster ${PREFAB_DEPENDENCIES} missile_medusa)
add_dependencies(monster_walker ${PREFAB_DEPENDENCIES} missile_medusa missile_enemy_bullet explosion_basic player)
add_dependencies(monster_flying ${PREFAB_DEPENDENCIES} missile_medusa missile_enemy_bullet explosion_basic player)

#Player
add_dependencies(player ${PREFAB_DEPENDENCIES} missile_laser)
add_dependencies(mate ${PREFAB_DEPENDENCIES} missile_laser)

set(PREFABS_TARGET 
	missile_medusa 
	missile_laser 
	missile_enemy_bullet 
	explosion_basic 
	player 
	mate
	monster 
	monster_walker 
	monster_flying
	beam)

add_custom_target(prefabs DEPENDS ${PREFABS_TARGET})