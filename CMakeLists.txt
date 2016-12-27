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
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /EHsc")

	#include files
	include_directories(include ${CMAKE_HOME_DIRECTORY}/Dependencies/SFML/Win/include ${CMAKE_HOME_DIRECTORY}/Dependencies/Boost/Win/include)

	#libraries files
	link_directories(${CMAKE_HOME_DIRECTORY}/Dependencies/SFML/Win/x64/Release)
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
include(${PROJECT_SOURCE_DIR}/R-Type/Network/CMakeLists.txt)

############## PROTOCOLS #############
include(${PROJECT_SOURCE_DIR}/R-Type/Protocol/Game/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/Protocol/Room/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/Protocol/Server/CMakeLists.txt)

############################## BINARIES ##############################
include(${PROJECT_SOURCE_DIR}/R-Type/ServerGameDispatcher/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/ServerRoom/CMakeLists.txt)

#TODO UTILISER GAMESERVER
############ GAMESERVER ##############
include(${PROJECT_SOURCE_DIR}/R-Type/GameServer/CMakeLists.txt)
#TODO UTILISER GAMECLIENT
############ GAMECLIENT ##############
include(${PROJECT_SOURCE_DIR}/R-Type/GameClient/CMakeLists.txt)

############### PREFABS ##############
include(${PROJECT_SOURCE_DIR}/R-Type/Prefab/CMakeLists.txt)

############### TESTS ################
#include(${PROJECT_SOURCE_DIR}/Tests/Network/ClientRoomConnectionToServerRoom/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/GameServer/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/Tests/Network/CMakeLists.txt)
#include(${PROJECT_SOURCE_DIR}/Tests/GUI/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/Animations/CMakeLists.txt)