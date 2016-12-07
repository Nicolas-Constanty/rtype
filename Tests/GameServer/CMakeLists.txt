cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

add_executable(gameserv-1
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${SaltyEnginesrc} ${SaltyEngineinc}
        ${srcGameServ} ${incGameServ}
        ${Protocolsrc} ${Protocolinc}
        Tests/GameServer/gameserv-1.cpp)

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

target_link_libraries(gameserv-1 -ldl)
target_link_libraries(gameserv-2 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)
target_link_libraries(gameclient-1 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so)