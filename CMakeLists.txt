cmake_minimum_required(VERSION 2.8)
project(rtype)

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SFML.zip)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

include_directories("include")

file(GLOB Networksrc src/Network/*/*.cpp)
file(GLOB Networkinc include/Network/*/*.hpp)

file(GLOB Commoninc include/Common/*.hpp)
file(GLOB Commonsrc src/Common/*.cpp)

file(GLOB Protocolsrc src/Protocol/*.cpp src/Protocol/*/*.cpp)
file(GLOB Protocolinc include/Protocol/*.hpp include/Protocol/*/*.hpp)

file(GLOB SaltyEnginesrc src/SaltyEngine/*.cpp src/SaltyEngine/GUI/*.cpp src/SaltyEngine/Input/*.cpp)
file(GLOB SaltyEngineinc include/SaltyEngine/*.hpp include/SaltyEngine/GUI/*.hpp include/SaltyEngine/Input/*.hpp)

file(GLOB SFMLsrc src/SaltyEngine/SFML/*.cpp)
file(GLOB SFMLinc include/SaltyEngine/SFML/*.hpp)

file(GLOB srcGameServ src/Rtype/Game/Server/*.cpp)
file(GLOB incGameServ include/Rtype/Game/Server/*.hpp)

file(GLOB srcGameCommon src/Rtype/Game/Common/*.cpp)
file(GLOB incGameCommon include/Rtype/Game/Common/*.hpp)

file(GLOB srcGameClient src/Rtype/Game/Client/*.cpp)
file(GLOB incGameClient include/Rtype/Game/Client/*.hpp)

file(GLOB allsrc src/*/*.cpp src/*/*/*.cpp)
file(GLOB allinc include/*/*.hpp include/*/*/*.hpp)

file(GLOB serverRoomsrc src/ServerRoom/*.cpp)
file(GLOB serverRoominc include/ServerRoom/*.hpp)

file(GLOB serverGameRoomssrc src/ServerGame/CreateRoomGameServer/*.cpp)
file(GLOB serverGameRoomsinc include/ServerGame/CreateRoomGameServer/*.hpp)

file(GLOB threadsrc src/Thread/*.cpp)
file(GLOB threadinc include/Thread/*.hpp)

file(GLOB processsrc src/Process/*.cpp)
file(GLOB processinc include/Process/*.hpp)

execute_process(COMMAND unzip -f ${CMAKE_SOURCE_DIR}/Dependencies/SFML.zip)
link_directories(${CMAKE_BINARY_DIR}/SFML/Linux/lib)
#
#add_executable(rtype-server
#        ${srcGameServ} ${incGameServ}
#        ${Networksrc} ${Networkinc}
#        ${Commoninc} ${Commonsrc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEnginesrc} ${SaltyEngineinc})
#
#add_executable(udpserv-1 ${Networksrc} ${Networkinc} Tests/Network/udpserv-1.cpp Tests/Network/baseudp.hpp)
#add_executable(tcpserv-1 ${Networksrc} ${Networkinc} Tests/Network/tcpserv-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)
#add_executable(udpserv-2 ${Networksrc} ${Networkinc} Tests/Network/udpserv-2.cpp Tests/Network/baseudp.hpp)
#add_executable(udpclient-1 ${Networksrc} ${Networkinc} Tests/Network/udpclient-1.cpp Tests/Network/baseudp.hpp)
#add_executable(gameserv-1
#        ${Networksrc} ${Networkinc}
#        ${Commoninc} ${Commonsrc}
#        ${SaltyEnginesrc} ${SaltyEngineinc}
#        ${srcGameServ} ${incGameServ}
#        ${Protocolsrc} ${Protocolinc}
#        Tests/GameServer/gameserv-1.cpp)
#add_executable(clientRoomTCPClient ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} Tests/Network/ClientRoomConnectionToServerRoom/tcpclient-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)
#add_executable(serverGameTCPClient ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} Tests/Network/ServerGameConnectionToServerRoom/serverGameTCP.cpp Tests/Network/ServerGameConnectionToServerRoom/serverGameClient.hpp)
#add_executable(serverGameLauncher ${processsrc} ${processinc} ${threadsrc} ${threadinc} ${serverGameRoomsinc} ${serverGameRoomssrc} ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} src/ServerGame/CreateRoomGameServer/main.cpp)
#
#add_executable(serverRoom
#        ${Networksrc} ${Networkinc}
#        ${Commoninc} ${Commonsrc}
#        ${Protocolsrc} ${Protocolinc}
#        ${serverRoomsrc} ${serverRoominc}
#        src/ServerRoom/main.cpp)
#
#add_executable(gameserv-2
#        ${Networksrc} ${Networkinc}
#        ${Commonsrc} ${Commoninc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEnginesrc} ${SaltyEngineinc}
#        ${srcGameServ} ${incGameServ}
#        ${srcGameCommon} ${incGameCommon}
#        ${SFMLsrc} ${SFMLinc}
#        Tests/GameServer/gameserv-2.cpp)
#
#add_executable(gameclient-1
#        ${Networksrc} ${Networkinc}
#        ${Commoninc} ${Commonsrc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEnginesrc} ${SaltyEngineinc}
#        ${srcGameClient} ${incGameClient}
#        ${srcGameCommon} ${incGameCommon}
#        ${SFMLsrc} ${SFMLinc}
#        Tests/GameServer/gameclient-1.cpp)
#
#add_executable(udp-reception-status include/Network/UDP/ReceptionStatus.hpp Tests/Network/udpreception-status.cpp)

#add_executable(toto Tests/SaltyEngine/main.cpp) #for color

#target_link_libraries(gameserv-1 -ldl)
#target_link_libraries(gameserv-2 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)
#target_link_libraries(gameclient-1 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)
#target_link_libraries(serverRoom -ldl)
#target_link_libraries(serverGameLauncher -ldl -lpthread)

#IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#    target_link_libraries(udpserv-1 -lWs2_32)
#    target_link_libraries(tcpserv-1 -lWs2_32)
#    target_link_libraries(udpserv-2 -lWs2_32)
#    target_link_libraries(udpserv-3 -lWs2_32)
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

############### NETWORK ###############
include(${PROJECT_SOURCE_DIR}/R-Type/Network/CMakeLIsts.txt)

############### SERVER ###############
include(${PROJECT_SOURCE_DIR}/R-Type/ServerRoom/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/ServerGameDispatcher/CMakeLists.txt)

############### PARSER ###############
include(${PROJECT_SOURCE_DIR}/R-Type/Parser/CMakeLists.txt)

############ SALTYENGINE #############
include(${PROJECT_SOURCE_DIR}/R-Type/SaltyEngine/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/R-Type/SFMLSaltyEngine/CMakeLists.txt)

############### TESTS ################
include(${PROJECT_SOURCE_DIR}/Tests/Network/ClientRoomConnectionToServerRoom/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/GameServer/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/Network/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/Adrien/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/Tests/GUI/CMakeLists.txt)
add_dependencies(client-test-move-netork prefabs)

############### PREFABS ##############
include(${PROJECT_SOURCE_DIR}/R-Type/Prefab/CMakeLists.txt)
add_custom_target(prefabs DEPENDS player mate missile_medusa monster missile_laser)
add_dependencies(SFMLSaltyEngine SaltyEngine)
add_dependencies(player SFMLSaltyEngine network)
add_dependencies(mate SaltyEngine)
add_dependencies(missile_medusa SFMLSaltyEngine)
add_dependencies(monster SFMLSaltyEngine)
add_dependencies(monster_walker SFMLSaltyEngine)
add_dependencies(missile_laser SFMLSaltyEngine)
add_dependencies(prefabs player mate missile_medusa monster missile_laser monster_walker)

### FULL BUILD ###
add_custom_target(BuildGUI DEPENDS gui)
add_dependencies(gui prefabs Parser)


add_dependencies(client-test-move-netork SaltyEngine SFMLSaltyEngine Parser)