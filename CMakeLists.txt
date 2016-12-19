cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

	find_package(PkgConfig)
	pkg_check_modules(SFML sfml-all)
	if ("${SFML_LIBRARIES}" STREQUAL "")
		execute_process(COMMAND unzip -u "${CMAKE_HOME_DIRECTORY}/Dependencies/SFML.zip")
		include_directories(include ${CMAKE_BINARY_DIR}/SFML/Linux/include)
		link_directories(${CMAKE_BINARY_DIR}/SFML/Linux/lib)
	endif()

	#Set Output Directories
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

#Windows
elseif(MSVC)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

############################## LIBRARIES ##############################
############### COMMON ###############
include(${PROJECT_SOURCE_DIR}/R-Type/Common/CMakeLists.txt)

############### PARSER ###############
include(${PROJECT_SOURCE_DIR}/R-Type/Parser/CMakeLists.txt)

############ SALTYENGINE #############
include(${PROJECT_SOURCE_DIR}/R-Type/SaltyEngine/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/SFMLSaltyEngine/CMakeLists.txt)

############### NETWORK ###############
#include(${PROJECT_SOURCE_DIR}/R-Type/Network/CMakeLists.txt)

############################## BINARIES ##############################
############### SERVER ###############
#include(${PROJECT_SOURCE_DIR}/R-Type/ServerRoom/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/R-Type/ServerGameDispatcher/CMakeLists.txt)


############### TESTS ################
#include(${PROJECT_SOURCE_DIR}/Tests/Network/ClientRoomConnectionToServerRoom/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/Tests/GameServer/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/Tests/Network/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/Tests/GUI/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/Animations/CMakeLists.txt)


############### PREFABS ##############
#include(${PROJECT_SOURCE_DIR}/R-Type/Prefab/CMakeLists.txt)




#!!!!!!!!!!!!!!!TODO DELETE AFTER THIS!!!!!!!!!!!!!!!!!

#file(GLOB Networksrc src/Network/*/*.cpp)
#file(GLOB Networkinc include/Network/*/*.hpp)
#
#file(GLOB Commoninc include/Common/*.hpp)
#file(GLOB Commonsrc src/Common/*.cpp)
#
#file(GLOB Protocolsrc src/Protocol/*.cpp src/Protocol/*/*.cpp)
#file(GLOB Protocolinc include/Protocol/*.hpp include/Protocol/*/*.hpp)
#
#file(GLOB SaltyEnginesrc src/SaltyEngine/*.cpp src/SaltyEngine/GUI/*.cpp src/SaltyEngine/Input/*.cpp)
#file(GLOB SaltyEngineinc include/SaltyEngine/*.hpp include/SaltyEngine/GUI/*.hpp include/SaltyEngine/Input/*.hpp)
#
#file(GLOB SFMLsrc src/SaltyEngine/SFML/*.cpp)
#file(GLOB SFMLinc include/SaltyEngine/SFML/*.hpp)
#
#file(GLOB srcGameServ src/Rtype/Game/Server/*.cpp)
#file(GLOB incGameServ include/Rtype/Game/Server/*.hpp)
#
#file(GLOB srcGameCommon src/Rtype/Game/Common/*.cpp)
#file(GLOB incGameCommon include/Rtype/Game/Common/*.hpp)
#
#file(GLOB srcGameClient src/Rtype/Game/Client/*.cpp)
#file(GLOB incGameClient include/Rtype/Game/Client/*.hpp)
#
#file(GLOB allsrc src/*/*.cpp src/*/*/*.cpp)
#file(GLOB allinc include/*/*.hpp include/*/*/*.hpp)
#
#file(GLOB serverRoomsrc src/ServerRoom/*.cpp)
#file(GLOB serverRoominc include/ServerRoom/*.hpp)
#
#file(GLOB serverGameRoomssrc src/ServerGame/CreateRoomGameServer/*.cpp)
#file(GLOB serverGameRoomsinc include/ServerGame/CreateRoomGameServer/*.hpp)
#
#file(GLOB threadsrc src/Thread/*.cpp)
#file(GLOB threadinc include/Thread/*.hpp)
#
#file(GLOB processsrc src/Process/*.cpp)
#file(GLOB processinc include/Process/*.hpp)

############# DEPENDENCIES ############
#add_dependencies(client-test-move-netork prefabs Parser)

#add_dependencies(gui Network Parser SFMLSaltyEngine prefabs)
#add_dependencies(gameserver-stable SaltyEngine SFMLSaltyEngine Parser)