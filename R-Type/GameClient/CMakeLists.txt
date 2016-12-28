cmake_minimum_required(VERSION 2.8)
project(rtype)

#include files
include_directories(include)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ FLAGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -DBUILD_SHARED_LIBS -DEXPORT_LIB")

	#C++ files
	file(GLOB GameClientSrc
			"src/Rtype/Game/Server/*.cpp"
			"src/Rtype/Game/Common/*.cpp"
			"src/Rtype/Game/Client/*.cpp"
			"src/Prefabs/RtypePrefab.cpp"
			"R-Type/GameClient/main.cpp"
			)

	#Hpp files
	file(GLOB GameClientInc
			"include/Rtype/Game/Server/*.hpp"
			"include/Rtype/Game/Common/*.hpp"
			"include/Rtype/Game/Common/*.hpp"
			)
	
	#Create GameClient
	add_executable(GameClient ${GameClientSrc} ${GameClientInc})

	#Link libraries
	target_link_libraries(GameClient
			Common
			Parser
			SaltyEngine
			SFMLSaltyEngine
			Network
			ProtocolServer
			ProtocolGame
			ProtocolRoom
			player
			missile_laser
			mate
			pod
			dl sfml-system sfml-audio sfml-graphics sfml-window)

	#Windows
elseif(MSVC)

	#C++ files
	file(GLOB GameClientSrc
			"../../R-Type/GameClient/main.cpp"
	)

	#Hpp files
	file(GLOB GameClientInc
			"../../include/Rtype/Game/Server/*.hpp"
			"../../include/Rtype/Game/Common/*.hpp"
			"../../include/Rtype/Game/Common/*.hpp"
	)

	#C++ FLAGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DRTYPESERVER -DNO_EXPORT")

	#Create GameClient
	add_executable(GameClient ${GameClientSrc} ${GameClientInc})

	#Link libraries
	target_link_libraries(GameClient
			Common
			Parser
			SaltyEngine
			SFMLSaltyEngine
			Network
			ProtocolServer
			ProtocolGame
			ProtocolRoom
			player
			missile_laser
			mate
			pod
			sfml-system-d sfml-audio-d sfml-graphics-d sfml-window-d)

	add_custom_command(TARGET GameClient
        POST_BUILD
        COMMAND cmd /c "MoveBinary & cd ..\\..\\..\\ & MoveBinary.bat")



endif()

add_dependencies(GameClient Common ProtocolServer ProtocolGame ProtocolRoom SaltyEngine SFMLSaltyEngine Parser prefabs)