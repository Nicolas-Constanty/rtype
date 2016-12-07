cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_executable(clientRoomTCPClient ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} Tests/Network/ClientRoomConnectionToServerRoom/tcpclient-1.cpp Tests/Network/ClientRoomConnectionToServerRoom/basetcp.hpp)

