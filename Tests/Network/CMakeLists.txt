cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_executable(udpserv-1 ${Networksrc} ${Networkinc} Tests/Network/udpserv-1.cpp Tests/Network/baseudp.hpp)
add_executable(tcpserv-1 ${Networksrc} ${Networkinc} Tests/Network/tcpserv-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)
add_executable(udpserv-2 ${Networksrc} ${Networkinc} Tests/Network/udpserv-2.cpp Tests/Network/baseudp.hpp)
add_executable(udpclient-1 ${Networksrc} ${Networkinc} Tests/Network/udpclient-1.cpp Tests/Network/baseudp.hpp)
add_executable(udp-reception-status include/Network/UDP/ReceptionStatus.hpp Tests/Network/udpreception-status.cpp)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(udpserv-1 -lWs2_32)
    target_link_libraries(tcpserv-1 -lWs2_32)
    target_link_libraries(udpserv-2 -lWs2_32)
    target_link_libraries(udpclient-1 -lWs2_32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")