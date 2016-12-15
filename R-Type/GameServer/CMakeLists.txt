cmake_minimum_required(VERSION 2.8)
project(rtype)

include_directories("${CMAKE_BINARY_DIR}/include")

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -DRTYPESERVER")

	#Create GameServer
	add_executable(GameServer ${Protocolsrc} ${srcGameClient} ${srcGameCommon})

	#Link libraries
	target_link_libraries(GameServer Parser SaltyEngine SFMLSaltyEngine player Network dl sfml-system sfml-audio sfml-graphics sfml-window)

#Windows
elseif(MSVC)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DRTYPESERVER")

	#Create GameServer
	add_executable(GameServer ${Protocolsrc} ${srcGameServ} ${srcGameCommon} ${srcGameClient} src/GameServer/main.cpp)

	#Link libraries
	target_link_libraries(GameServer Parser SaltyEngine SFMLSaltyEngine player Network sfml-system sfml-audio sfml-graphics sfml-window)

endif()