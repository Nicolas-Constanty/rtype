#cmake_minimum_required(VERSION 3.6)
#project(rtype)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#
#include_directories("include")
#
#file(GLOB Networksrc src/Network/*/*.cpp)
#file(GLOB Networkinc include/Network/*/*.hpp)
#
#file(GLOB Commoninc include/Common/*.hpp)
#
#file(GLOB Protocolsrc src/Protocol/*.cpp)
#file(GLOB Protocolinc include/Protocol/*.hpp)
#
#file(GLOB SaltyEnginesrc src/SaltyEngine/*.cpp)
#file(GLOB SaltyEngineinc include/SaltyEngine/*.hpp)
#
#file(GLOB allsrc src/*/*.cpp src/*/*/*.cpp)
#file(GLOB allinc src/*/*.hpp src/*/*/*.hpp)
#
#add_executable(rtype-server
#        ${Networksrc} ${Networkinc}
#        ${Commoninc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEnginesrc} ${SaltyEngineinc})
#
#add_executable(udpserv-1 ${Networksrc} ${Networkinc} Tests/Network/udpserv-1.cpp)
#add_executable(tcpserv-1 ${Networksrc} ${Networkinc} Tests/Network/tcpserv-1.cpp)
#add_executable(udpserv-2 ${Networksrc} ${Networkinc} Tests/Network/udpserv-2.cpp)
#
#IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#    target_link_libraries(udpserv-1 -lWs2_32)
#    target_link_libraries(tcpserv-1 -lWs2_32)
#    target_link_libraries(tcpserv-2 -lWs2_32)
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

cmake_minimum_required(VERSION 2.8)
project(rtype)

execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SFML.zip)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILE
        "src/SaltyEngine/*.cpp"
        "src/SaltyEngine/Input/*.cpp"
        "src/SaltyEngine/SFML/*.cpp"
        )
file(GLOB INCLUDE_FILE
        "include/SaltyEngine/*.hpp"
        "include/SaltyEngine/Input/*.hpp"
        "include/SaltyEngine/SFML/*.hpp")

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
execute_process(COMMAND unzip -f ${CMAKE_SOURCE_DIR}/Dependencies/SFML.zip)
link_directories(${CMAKE_BINARY_DIR}/SFML/Linux/lib)

file(GLOB threadsrc src/Thread/*.cpp)
file(GLOB threadinc include/Thread/*.hpp)

add_executable(rtype-server
        ${srcGameServ} ${incGameServ}
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEnginesrc} ${SaltyEngineinc})

add_executable(udpserv-1 ${Networksrc} ${Networkinc} Tests/Network/udpserv-1.cpp Tests/Network/baseudp.hpp)
add_executable(tcpserv-1 ${Networksrc} ${Networkinc} Tests/Network/tcpserv-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)
add_executable(udpserv-2 ${Networksrc} ${Networkinc} Tests/Network/udpserv-2.cpp Tests/Network/baseudp.hpp)
add_executable(udpclient-1 ${Networksrc} ${Networkinc} Tests/Network/udpclient-1.cpp Tests/Network/baseudp.hpp)
add_executable(gameserv-1
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${SaltyEnginesrc} ${SaltyEngineinc}
        ${srcGameServ} ${incGameServ}
        ${Protocolsrc} ${Protocolinc}
        Tests/GameServer/gameserv-1.cpp)
add_executable(clientRoomTCPClient ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} Tests/Network/ClientRoomConnectionToServerRoom/tcpclient-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)
add_executable(serverGameTCPClient ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} Tests/Network/ServerGameConnectionToServerRoom/serverGameTCP.cpp Tests/Network/ServerGameConnectionToServerRoom/serverGameClient.hpp)
add_executable(serverGameLauncher ${threadsrc} ${threadinc} ${serverGameRoomsinc} ${serverGameRoomssrc} ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} src/ServerGame/CreateRoomGameServer/main.cpp)

add_executable(serverRoom
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${serverRoomsrc} ${serverRoominc}
        src/ServerRoom/main.cpp)

add_executable(gameserv-2
        ${Networksrc} ${Networkinc}
        ${Commonsrc} ${Commoninc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEnginesrc} ${SaltyEngineinc}
        ${srcGameServ} ${incGameServ}
        ${srcGameCommon} ${incGameCommon}
        ${SFMLsrc} ${SFMLinc}
        Tests/GameServer/gameserv-2.cpp)

add_executable(gameclient-1
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEnginesrc} ${SaltyEngineinc}
        ${srcGameClient} ${incGameClient}
        ${srcGameCommon} ${incGameCommon}
        ${SFMLsrc} ${SFMLinc}
        Tests/GameServer/gameclient-1.cpp)

add_executable(udp-reception-status include/Network/UDP/ReceptionStatus.hpp Tests/Network/udpreception-status.cpp)

#add_executable(toto Tests/SaltyEngine/main.cpp) #for color

target_link_libraries(gameserv-1 -ldl)
target_link_libraries(gameserv-2 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)
target_link_libraries(gameclient-1 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)
target_link_libraries(serverRoom -ldl)
target_link_libraries(serverGameLauncher -ldl -lpthread)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(udpserv-1 -lWs2_32)
    target_link_libraries(tcpserv-1 -lWs2_32)
    target_link_libraries(udpserv-2 -lWs2_32)
    target_link_libraries(udpserv-3 -lWs2_32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


############### PREFABS ###############
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Assets/Monsters)

include_directories("include" "Dependencies/SFML/Linux/include")

# MONSTER
file(GLOB MONSTER_SOURCE_FILE "src/Monster/*.cpp")
add_library(monster SHARED ${MONSTER_SOURCE_FILE})
target_link_libraries(monster ${PROJECT_SOURCE_DIR}/R-Type/SaltyEngine/libSaltyEngine.a -ldl)

# MISSILE MEDUSA
file(GLOB MISSILE_MEDUSA_SOURCE_FILE "src/Missile/MissileMedusa/*.cpp" "src/Missile/*.cpp")
add_library(missile_medusa SHARED ${MISSILE_MEDUSA_SOURCE_FILE})
target_link_libraries(missile_medusa ${PROJECT_SOURCE_DIR}/R-Type/SaltyEngine/libSaltyEngine.a -ldl)

# PLAYER
file(GLOB PLAYER_SOURCE_FILE "src/Player/*.cpp")
add_library(player SHARED ${PLAYER_SOURCE_FILE})
target_link_libraries(player ${PROJECT_SOURCE_DIR}/R-Type/SaltyEngine/libSaltyEngine.a -ldl)