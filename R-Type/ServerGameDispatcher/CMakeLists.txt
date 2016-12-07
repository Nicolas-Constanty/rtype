cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_executable(serverGameDispatcher ${processsrc} ${processinc} ${threadsrc} ${threadinc} ${serverGameRoomsinc} ${serverGameRoomssrc} ${Networksrc} ${Networkinc} ${Protocolinc} ${Protocolsrc} src/ServerGame/CreateRoomGameServer/main.cpp)

target_link_libraries(serverGameDispatcher -ldl -lpthread)