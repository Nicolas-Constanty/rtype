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

cmake_minimum_required(VERSION 3.6)
project(rtype)

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

file(GLOB SaltyEnginesrc src/SaltyEngine/*.cpp src/SaltyEngine/GUI/*.cpp src/SaltyEngine/Input/*.cpp src/SaltyEngine/SFML/*.cpp src/Monster/*.cpp src/ClientLauncher/*.cpp)
file(GLOB SaltyEngineinc include/SaltyEngine/*.hpp include/SaltyEngine/GUI/*.hpp include/SaltyEngine/Input/*.hpp include/SaltyEngine/SFML/*.hpp include/Monster/*.hpp include/ClientLauncher/*.hpp)

file(GLOB srcGameServ src/ServerGame/*.cpp)
file(GLOB incGameServ include/ServerGame/*.hpp)

file(GLOB allsrc src/*/*.cpp src/*/*/*.cpp)
file(GLOB allinc include/*/*.hpp include/*/*/*.hpp)

file(GLOB serverRoomsrc src/ServerRoom/*.cpp)
file(GLOB serverRoominc include/ServerRoom/*.hpp)


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

add_executable(serverRoom
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${serverRoomsrc} ${serverRoominc}
        src/ServerRoom/main.cpp)

#add_executable(toto Tests/SaltyEngine/main.cpp) #for color

target_link_libraries(gameserv-1 -ldl)
target_link_libraries(serverRoom -ldl)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(udpserv-1 -lWs2_32)
    target_link_libraries(tcpserv-1 -lWs2_32)
    target_link_libraries(udpserv-2 -lWs2_32)
    target_link_libraries(udpserv-3 -lWs2_32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")