cmake_minimum_required(VERSION 2.8)
project(rtype)

#include files
include_directories(include)

#C++ files
file(GLOB GameClientSrc "src/Rtype/Game/Client/*.cpp" "src/Rtype/Game/Common/*.cpp")

#Hpp files
file(GLOB GameClientInc "include/Rtype/Game/Client/*.hpp" "include/Rtype/Game/Common/*.hpp")


#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -DRTYPESERVER")

	#Create GameServer
	add_executable(GameClient ${GameClientSrc} ${GameServerInc})

	#Link libraries
	target_link_libraries(GameClient Parser SaltyEngine SFMLSaltyEngine player Network dl sfml-system sfml-audio sfml-graphics sfml-window)

#Windows
elseif(MSVC)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DRTYPESERVER")

	#Create GameClient
	add_executable(GameClient ${GameClientSrc} ${GameServerInc})

	#Link libraries
	target_link_libraries(GameClient Parser SaltyEngine SFMLSaltyEngine player Network sfml-system sfml-audio sfml-graphics sfml-window)

endif()