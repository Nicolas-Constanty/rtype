cmake_minimum_required(VERSION 2.8)
project(rtype CXX)

include_directories("include")


#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

file(GLOB SRC_RTYPE
	"src/Rtype/Game/Client/*.cpp"
	"src/Rtype/Game/Server/*.cpp"
	"src/Rtype/Game/Common/*.cpp"
)

file(GLOB SRC_COMMMUNICATION
	"src/Rtype/Game/Client/*.cpp"
	"src/Rtype/Game/Server/*.cpp"
	"src/Rtype/Game/Common/*.cpp"
	"src/Prefabs/Player/PlayerController.cpp"
	"src/Prefabs/RtypePrefab.cpp"
	"src/Prefabs/CommonPlayer/CommonPlayerController.cpp"
	"src/Prefabs/Mate/MateComponent.cpp"
	"src/Prefabs/Missile/Laser/LaserController.cpp"
	"src/Prefabs/Pod/PodController.cpp"
	"src/Prefabs/GenericController.cpp"
	"src/Prefabs/PodHandler/PodHandler.cpp"
	"src/Prefabs/PositionReplicator/PositionReplicator.cpp"
)

	add_library(PrefabCommunication SHARED ${SRC_COMMMUNICATION})
	target_link_libraries(PrefabCommunication SaltyEngine SFMLSaltyEngine Network Parser ProtocolGame)

	add_dependencies(PrefabCommunication SFMLSaltyEngine ProtocolGame)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/Assets/Metas)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -g -rdynamic")

	set(PREFAB_LIBRARIES SaltyEngine Network dl)

	# GAME MANAGER
	file(GLOB MANAGER_SOURCE_FILE "src/Prefabs/GameManager/*.cpp"  "include/Prefabs/GameManager/*.hpp")
	add_library(game_manager SHARED ${MANAGER_SOURCE_FILE})
	target_link_libraries(game_manager ${PREFAB_LIBRARIES})

	# BLOCK
	file(GLOB BEAM_SOURCE_FILE "src/Prefabs/Block/*.cpp"  "include/Prefabs/Block/*.hpp")
	add_library(BlockSimple SHARED ${BEAM_SOURCE_FILE})
	target_link_libraries(BlockSimple ${PREFAB_LIBRARIES})

	# BEAM
	file(GLOB BEAM_SOURCE_FILE "src/Prefabs/Beam/*.cpp"  "include/Prefabs/Beam/*.hpp")
	add_library(beam SHARED ${BEAM_SOURCE_FILE})
	target_link_libraries(beam ${PREFAB_LIBRARIES})

	# BONUS
	file(GLOB BONUS_INC include/Prefabs/Bonus/*.hpp)
	file(GLOB BONUS_SRC src/Prefabs/Bonus/*.cpp)
	add_library(spiralbonus SHARED ${BONUS_SRC} ${BONUS_INC})
	target_link_libraries(spiralbonus ${PREFAB_LIBRARIES})


	# MISSILES

		# MISSILE MEDUSA
		file(GLOB MISSILE_MEDUSA_SOURCE_FILE
				"src/Prefabs/Missile/MissileMedusa/*.cpp" "src/Prefabs/Missile/*.cpp"
				"include/Prefabs/Missile/*.hpp" "include/Prefabs/Missile/MissileMedusa/*.hpp")
		add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
		target_link_libraries(missile_medusa ${PREFAB_LIBRARIES})

		# MISSILE NEUNOEIL
		file(GLOB MISSILE_NEUNOEIL_SOURCE_FILE
				"src/Prefabs/Missile/MissileNeunoeil/*.cpp" "src/Prefabs/Missile/*.cpp"
				"include/Prefabs/Missile/*.hpp" "include/Prefabs/Missile/MissileNeunoeil/*.hpp")
		add_library(missile_neunoeil SHARED ${MISSILE_NEUNOEIL_SOURCE_FILE})
		target_link_libraries(missile_neunoeil ${PREFAB_LIBRARIES})

		# MISSILE HOMING
		file(GLOB MISSILE_HOMING_SOURCE_FILE
				"src/Prefabs/Missile/MissileHoming/*.cpp" "src/Prefabs/Missile/*.cpp"
				"include/Prefabs/Missile/*.hpp" "include/Prefabs/Missile/MissileHoming/*.hpp")
		add_library(missile_homing SHARED ${MISSILE_HOMING_SOURCE_FILE})
		target_link_libraries(missile_homing ${PREFAB_LIBRARIES})

		# MISSILE LASER
		file(GLOB MISSILE_LASER_SOURCE_FILE
				"src/Prefabs/Missile/Laser/*.cpp"
				"include/Prefabs/Missile/Laser/*.hpp")
		add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})

		# MISSILE LASER SPIRAL
		file(GLOB MISSILE_LASER_SPIRAL_SOURCE_FILE
				"src/Prefabs/Missile/LaserSpiral/*.cpp"
				"include/Prefabs/Missile/LaserSpiral/*.hpp")
		add_library(missile_laser_spiral SHARED ${MISSILE_LASER_SPIRAL_SOURCE_FILE})
		target_link_libraries(missile_laser_spiral ${PREFAB_LIBRARIES})

		target_link_libraries(missile_laser ${PREFAB_LIBRARIES})

		# DEFAULT ENEMY BULLET
		file(GLOB MISSILE_ENEMY_BULLET
				"src/Prefabs/Missile/EnemyBullet/*.cpp"
				"include/Prefabs/Missile/EnemyBullet/*.hpp")
		add_library(missile_enemy_bullet SHARED ${MISSILE_ENEMY_BULLET})
		target_link_libraries(missile_enemy_bullet ${PREFAB_LIBRARIES})

	# BASIC EXPLOSION
	file(GLOB EXPLOSIONBASIC_SOURCE_FILE
			"src/Prefabs/ExplosionBasic/*.cpp"
			"include/Prefabs/ExplosionBasic/*.hpp")
	add_library(explosion_basic SHARED ${EXPLOSIONBASIC_SOURCE_FILE})
	target_link_libraries(explosion_basic ${PREFAB_LIBRARIES})

	# SPACESHIPS

		# PLAYER
		file(GLOB PLAYER_SOURCE_FILE "src/Prefabs/Player/*.cpp" "src/Prefabs/PodHandler/*.cpp" "src/Prefabs/CommonPlayer/*.cpp")
		file(GLOB PLAYER_INC_FILE "include/Prefabs/Player/*.hpp" "include/Prefabs/PodHandler/*.hpp" "include/Prefabs/CommonPlayer/*.hpp")
		add_library(player SHARED ${PLAYER_SOURCE_FILE} ${PLAYER_INC_FILE})
		target_link_libraries(player ${PREFAB_LIBRARIES} missile_laser)

		# MATE (network managed client)
		file(GLOB MATE_SOURCE_FILES "src/Prefabs/Mate/*.cpp" "src/Prefabs/PodHandler/*.cpp" "src/Prefabs/CommonPlayer/*.cpp")
		file(GLOB MATE_INC_FILES "include/Prefabs/Mate/*.hpp" "include/Prefabs/PodHandler/*.hpp" "include/Prefabs/CommonPlayer/*.hpp")
		add_library(mate SHARED ${MATE_SOURCE_FILES} ${MATE_INC_FILES})
		target_link_libraries(mate ${PREFAB_LIBRARIES} missile_laser)

		# POD
		file(GLOB POD_SOURCE_FILES "src/Prefabs/Pod/*.cpp" "src/Prefabs/PodHandler/*.cpp" )
		file(GLOB POD_INC_FILES "include/Prefabs/Pod/*.hpp" "include/Prefabs/PodHandler/*.hpp")
		add_library(pod SHARED ${POD_SOURCE_FILES} ${POD_INC_FILES})
		target_link_libraries(pod ${PREFAB_LIBRARIES})

	# MONSTERS

		# BASIC
		file(GLOB MONSTER_SOURCE_FILE
				"src/Prefabs/Monster/*.cpp"
				"include/Prefabs/Monster/*.hpp"
				"include/Prefabs/GenericController.hpp"
				"src/Prefabs/PositionReplicator/*.cpp"
				"include/Prefabs/PositionReplicator/*.hpp")
		add_library(monster SHARED ${MONSTER_SOURCE_FILE})
		target_link_libraries(monster ${PREFAB_LIBRARIES} missile_medusa)

		# WALKER
		file(GLOB WALKINGMONSTER_SOURCE_FILE
				"src/Prefabs/MonsterWalker/*.cpp"
				"include/Prefabs/MonsterWalker/*.hpp"
				"src/Prefabs/PositionReplicator/*.cpp"
				"include/Prefabs/PositionReplicator/*.hpp")
		add_library(monster_walker SHARED ${WALKINGMONSTER_SOURCE_FILE})
		target_link_libraries(monster_walker ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

		# FLYING
		file(GLOB FLYINGMONSTER_SOURCE_FILE
				"src/Prefabs/MonsterFlying/*.cpp"
				"include/Prefabs/MonsterFlying/*.hpp"
				"src/Prefabs/PositionReplicator/*.cpp"
				"include/Prefabs/PositionReplicator/*.hpp")
		add_library(monster_flying SHARED ${FLYINGMONSTER_SOURCE_FILE})
		target_link_libraries(monster_flying ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic)

	# BOSSES

		# NEUNOEIL
		file(GLOB NEUNOEILMONSTER_SOURCE_FILE
				"src/Prefabs/MonsterNeunoeil/*.cpp"
				"include/Prefabs/MonsterNeunoeil/*.hpp"
				"src/Prefabs/PositionReplicator/*.cpp"
				"include/Prefabs/PositionReplicator/*.hpp")
		add_library(monster_neunoeil SHARED ${NEUNOEILMONSTER_SOURCE_FILE})
		target_link_libraries(monster_neunoeil ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

		# MEDUSA
		file(GLOB MEDUSAMONSTER_SOURCE_FILE
				"src/Prefabs/MonsterMedusa/*.cpp"
				"include/Prefabs/MonsterMedusa/*.hpp"
				"src/Prefabs/PositionReplicator/*.cpp"
				"include/Prefabs/PositionReplicator/*.hpp")
		add_library(monster_medusa SHARED ${MEDUSAMONSTER_SOURCE_FILE})
		target_link_libraries(monster_medusa ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

	# GUI
        # LOG SCREEN
		file(GLOB GUI_LOGGER_SOURCE_FILE
				"src/ClientLauncher/*.cpp"
				"include/ClientLauncher/*.hpp")
		add_library(gui_logger SHARED ${GUI_LOGGER_SOURCE_FILE})
		target_link_libraries(gui_logger ${PREFAB_LIBRARIES})

		set(PREFAB_DEPENDENCIES SFMLSaltyEngine Network PrefabCommunication Common ProtocolGame)

	#Windows
elseif(MSVC)
file(GLOB SRC_RTYPE
	"../../src/Rtype/Game/Client/*.cpp"
	"../../src/Rtype/Game/Server/*.cpp"
	"../../src/Rtype/Game/Common/*.cpp"
)

file(GLOB SRC_COMMMUNICATION
	"../../src/Rtype/Game/Client/*.cpp"
	"../../src/Rtype/Game/Server/*.cpp"
	"../../src/Rtype/Game/Common/*.cpp"
	"../../src/Prefabs/Player/PlayerController.cpp"
	"../../src/Prefabs/RtypePrefab.cpp"
	"../../src/Prefabs/CommonPlayer/CommonPlayerController.cpp"
	"../../src/Prefabs/Mate/MateComponent.cpp"
	"../../src/Prefabs/Missile/Laser/LaserController.cpp"
	"../../src/Prefabs/Pod/PodController.cpp"
	"../../src/Prefabs/GenericController.cpp"
	"../../src/Prefabs/PodHandler/PodHandler.cpp"
	"../../src/Prefabs/PositionReplicator/PositionReplicator.cpp"
)

#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#C++ FLAGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES -DBUILD_SHARED_LIBS -DEXPORT_LIB")

	add_library(RtypeLib OBJECT 
		${SRC_RTYPE}
		"../../src/Prefabs/RtypePrefab.cpp"
		"../../src/Prefabs/PositionReplicator/PositionReplicator.cpp"
		
	)

	add_library(CommonPrefabs OBJECT
		"../../src/Prefabs/CommonPlayer/CommonPlayerController.cpp"
		"../../src/Prefabs/Player/PlayerController.cpp"
		"../../src/Prefabs/Missile/Laser/LaserController.cpp"
		"../../src/Prefabs/Pod/PodController.cpp"
		"../../src/Prefabs/PodHandler/PodHandler.cpp"
		"../../src/Prefabs/Mate/MateComponent.cpp"
	)

	set(PREFAB_LIBRARIES SaltyEngine SFMLSaltyEngine Network ProtocolGame)
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBUILD_SHARED_LIBS -DEXPORT_PREF")
	
	# BLOCK
	file(GLOB BEAM_SOURCE_FILE "../../src/Prefabs/Block/*.cpp")
	add_library(BlockSimple SHARED ${BEAM_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(BlockSimple ${PREFAB_LIBRARIES})

	# BEAM
	file(GLOB BEAM_SOURCE_FILE "../../src/Prefabs/Beam/*.cpp" )
	add_library(beam SHARED ${BEAM_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs> ../../src/SaltyEngine/SFML/TextBox.cpp ../../include/SaltyEngine/SFML/TextBox.hpp)
	target_link_libraries(beam ${PREFAB_LIBRARIES})
	# BONUS
	file(GLOB BONUS_SRC "../../src/Prefabs/Bonus/*.cpp")
	add_library(spiralbonus SHARED ${BONUS_SRC} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(spiralbonus ${PREFAB_LIBRARIES})

	# MISSILES

		file(GLOB LIB_MISSILE_SRC "../../src/Prefabs/Missile/*.cpp")
		add_library(Missile SHARED ${LIB_MISSILE_SRC} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(Missile ${PREFAB_LIBRARIES})

		# MISSILE MEDUSA
		file(GLOB MISSILE_MEDUSA_SOURCE_FILE "../../src/Prefabs/Missile/MissileMedusa/*.cpp")
		add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(missile_medusa ${PREFAB_LIBRARIES} Missile)

		# MISSILE NEUNOEIL
		file(GLOB MISSILE_NEUNOEIL_SOURCE_FILE "../../src/Prefabs/Missile/MissileNeunoeil/*.cpp")
		add_library(missile_neunoeil SHARED ${MISSILE_NEUNOEIL_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(missile_neunoeil ${PREFAB_LIBRARIES} Missile)

		# MISSILE HOMING
		file(GLOB MISSILE_HOMING_SOURCE_FILE "../../src/Prefabs/Missile/MissileHoming/*.cpp")
		add_library(missile_homing SHARED ${MISSILE_HOMING_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(missile_homing ${PREFAB_LIBRARIES} Missile)

		# MISSILE LASER
		file(GLOB MISSILE_LASER_SOURCE_FILE "../../src/Prefabs/Missile/Laser/*.cpp")
		add_library(missile_laser SHARED ${MISSILE_LASER_SOURCE_FILE})
		target_link_libraries(missile_laser ${PREFAB_LIBRARIES} Missile)

		# MISSILE LASER SPIRAL
		file(GLOB MISSILE_LASER_SPIRAL_SOURCE_FILE  "../../src/Prefabs/Missile/LaserSpiral/*.cpp")
		add_library(missile_laser_spiral SHARED ${MISSILE_LASER_SPIRAL_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(missile_laser_spiral ${PREFAB_LIBRARIES} Missile)

		# DEFAULT ENEMY BULLET
		file(GLOB MISSILE_ENEMY_BULLET "../../src/Prefabs/Missile/EnemyBullet/*.cpp")
		add_library(missile_enemy_bullet SHARED ${MISSILE_ENEMY_BULLET} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(missile_enemy_bullet ${PREFAB_LIBRARIES} Missile)

		# BASIC EXPLOSION
		file(GLOB EXPLOSIONBASIC_SOURCE_FILE "../../src/Prefabs/ExplosionBasic/*.cpp")
		add_library(explosion_basic SHARED ${EXPLOSIONBASIC_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
		target_link_libraries(explosion_basic ${PREFAB_LIBRARIES})

	# SPACESHIPS

	# PLAYER
	file(GLOB PLAYER_SOURCE_FILE "../../src/Prefabs/Player/*.cpp")
	add_library(player SHARED ${PLAYER_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib>)
	target_link_libraries(player ${PREFAB_LIBRARIES} missile_laser)

	# MATE (network managed client)
	file(GLOB MATE_SOURCE_FILES "../../src/Prefabs/Mate/*.cpp")
	add_library(mate SHARED ${MATE_SOURCE_FILES} $<TARGET_OBJECTS:RtypeLib>)
	target_link_libraries(mate ${PREFAB_LIBRARIES} missile_laser)

	# POD
	file(GLOB POD_SOURCE_FILES
		"../../src/Prefabs/Pod/*.cpp"
		"../../src/Prefabs/PodHandler/PodHandler.cpp"
	)
	add_library(pod SHARED ${POD_SOURCE_FILES} $<TARGET_OBJECTS:RtypeLib>)
	target_link_libraries(pod ${PREFAB_LIBRARIES} missile_laser)

	# MONSTERS

	# BASIC
	file(GLOB MONSTER_SOURCE_FILE "../../src/Prefabs/Monster/*.cpp")
	add_library(monster SHARED ${MONSTER_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(monster ${PREFAB_LIBRARIES} missile_medusa missile_laser)

	# WALKER
	file(GLOB WALKINGMONSTER_SOURCE_FILE "../../src/Prefabs/MonsterWalker/*.cpp")
	add_library(monster_walker SHARED ${WALKINGMONSTER_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(monster_walker ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

	# FLYING
	file(GLOB FLYINGMONSTER_SOURCE_FILE "../../src/Prefabs/MonsterFlying/*.cpp")
	add_library(monster_flying SHARED ${FLYINGMONSTER_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(monster_flying ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic)

	# BOSSES

	# WALKER
	file(GLOB NEUNOEILMONSTER_SOURCE_FILE "../../src/Prefabs/MonsterNeunoeil/*.cpp")
	add_library(monster_neunoeil SHARED ${NEUNOEILMONSTER_SOURCE_FILE} $<TARGET_OBJECTS:RtypeLib> $<TARGET_OBJECTS:CommonPrefabs>)
	target_link_libraries(monster_neunoeil ${PREFAB_LIBRARIES} missile_medusa missile_enemy_bullet explosion_basic player)

	set(PREFAB_DEPENDENCIES SFMLSaltyEngine Network Common ProtocolGame)

endif()


#BEAM
add_dependencies(beam ${PREFAB_DEPENDENCIES})

#Missiles
add_dependencies(missile_medusa ${PREFAB_DEPENDENCIES})
add_dependencies(missile_homing ${PREFAB_DEPENDENCIES})
add_dependencies(missile_laser ${PREFAB_DEPENDENCIES})
add_dependencies(missile_laser_spiral ${PREFAB_DEPENDENCIES})
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
		missile_neunoeil
        missile_homing
		missile_laser
		missile_laser_spiral
		missile_enemy_bullet
		explosion_basic
		player
		mate
        pod
        spiralbonus
		monster
		monster_walker
		monster_flying
		monster_neunoeil
		monster_medusa
		beam
		BlockSimple
        game_manager
        gui_logger)

add_custom_target(prefabs DEPENDS ${PREFABS_TARGET})