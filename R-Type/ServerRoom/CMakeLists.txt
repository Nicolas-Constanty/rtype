cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_executable(serverRoom
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${serverRoomsrc} ${serverRoominc}
        src/ServerRoom/main.cpp)

target_link_libraries(serverRoom -ldl)