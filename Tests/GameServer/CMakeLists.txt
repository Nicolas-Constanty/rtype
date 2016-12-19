cmake_minimum_required(VERSION 2.8)
project(rtype)


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()


#!!!!!!!!!!!!!!!TODO DELETE AFTER THIS!!!!!!!!!!!!!!!!!

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

#!!!!!!!!!!!!!!!TODO DELETE BEFORE THIS!!!!!!!!!!!!!!!!!

#add_executable(gameserv-1
#        ${Networksrc} ${Networkinc}
#        ${Commoninc} ${Commonsrc}
#        ${SaltyEnginesrc} ${SaltyEngineinc}
#        ${srcGameServ} ${incGameServ}
#        ${Protocolsrc} ${Protocolinc}
#        Tests/GameServer/gameserv-1.cpp)

#add_executable(gameserv-2
#        ${Networksrc} ${Networkinc}
#        ${Commonsrc} ${Commoninc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEnginesrc} ${SaltyEngineinc}
#        ${srcGameServ} ${incGameServ}
#        ${srcGameCommon} ${incGameCommon}
#        ${SFMLinc}
#        Tests/GameServer/gameserv-2.cpp)

#add_executable(gameclient-1
#        ${Networksrc} ${Networkinc}
#        ${Commoninc}
#        ${Protocolsrc} ${Protocolinc}
#        ${SaltyEngineinc}
#        ${srcGameClient} ${incGameClient}
#        ${srcGameCommon} ${incGameCommon}
#        ${SFMLinc}
#        Tests/GameServer/gameclient-1.cpp)

add_executable(gameserver-stable
        ${Networksrc} ${Networkinc}
        ${Commoninc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEngineinc}
        ${srcGameServ} ${incGameServ}
        ${srcGameCommon} ${incGameCommon}
        ${SFMLinc}
        ${srcGameClient} ${incGameClient}
        src/Prefabs/Player/PlayerController.cpp
        include/Prefabs/Player/PlayerController.hpp
        src/Prefabs/Mate/MateComponent.cpp
        include/Prefabs/Mate/MateComponent.hpp
        src/Prefabs/Missile/Laser/Laser.cpp
        src/Prefabs/Missile/Laser/LaserController.cpp
        include/Prefabs/Missile/Laser/Laser.hpp
        include/Prefabs/Missile/Laser/LaserController.hpp
        include/Prefabs/GenericController.hpp
        include/Prefabs/RtypePrefab.hpp
        src/Prefabs/RtypePrefab.cpp
        Tests/GameServer/gameserver-stable.cpp)

set_target_properties(gameserver-stable PROPERTIES COMPILE_FLAGS "-DRTYPESERVER")

add_executable(client-test-move-netork
        ${Networksrc} ${Networkinc}
        ${Commoninc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEngineinc}
        ${srcGameServ} ${incGameServ}
        ${srcGameClient} ${incGameClient}
        ${srcGameCommon} ${incGameCommon}
        ${SFMLinc}
        src/Prefabs/Missile/Laser/Laser.cpp
        src/Prefabs/Missile/Laser/LaserController.cpp
        src/Prefabs/Mate/MateComponent.cpp
        include/Prefabs/Mate/MateComponent.hpp
        include/Prefabs/Missile/Laser/Laser.hpp
        include/Prefabs/Missile/Laser/LaserController.hpp
        src/Prefabs/Player/PlayerController.cpp
        include/Prefabs/Player/PlayerController.hpp
        include/Prefabs/RtypePrefab.hpp
        src/Prefabs/RtypePrefab.cpp
        src/Prefabs/Player/PlayerController.cpp
        Tests/GameServer/main.cpp)

#target_link_libraries(gameserv-1 -ldl)
#target_link_libraries(gameserv-2 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so)
#target_link_libraries(gameclient-1 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so)
target_link_libraries(gameserver-stable dl sfml-system sfml-audio sfml-graphics sfml-window SaltyEngine SFMLSaltyEngine Parser pod)
target_link_libraries(client-test-move-netork dl sfml-system sfml-audio sfml-graphics sfml-window SaltyEngine SFMLSaltyEngine Parser pod)

add_dependencies(gameserver-stable SaltyEngine SFMLSaltyEngine Parser)
add_dependencies(client-test-move-netork prefabs Parser)