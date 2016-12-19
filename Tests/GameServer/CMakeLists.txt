cmake_minimum_required(VERSION 2.8)
project(rtype)


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()


#!!!!!!!!!!!!!!!TODO DELETE AFTER THIS!!!!!!!!!!!!!!!!!

file(GLOB srcGameServ src/Rtype/Game/Server/*.cpp)
file(GLOB incGameServ include/Rtype/Game/Server/*.hpp)

file(GLOB srcGameCommon src/Rtype/Game/Common/*.cpp)
file(GLOB incGameCommon include/Rtype/Game/Common/*.hpp)

file(GLOB srcGameClient src/Rtype/Game/Client/*.cpp)
file(GLOB incGameClient include/Rtype/Game/Client/*.hpp)

#!!!!!!!!!!!!!!!TODO DELETE BEFORE THIS!!!!!!!!!!!!!!!!!

add_executable(gameserver-stable
        ${srcGameServ} ${incGameServ}
        ${srcGameCommon} ${incGameCommon}
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
        R-Type/GameServer/main.cpp)

set_target_properties(gameserver-stable PROPERTIES COMPILE_FLAGS "-DRTYPESERVER")

add_executable(client-test-move-netork
        ${srcGameServ} ${incGameServ}
        ${srcGameClient} ${incGameClient}
        ${srcGameCommon} ${incGameCommon}
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
        R-Type/GameClient/main.cpp)

target_link_libraries(gameserver-stable
        Common
        Parser
        SaltyEngine
        SFMLSaltyEngine
        ProtocolServer
        ProtocolGame
        ProtocolRoom
        dl sfml-system sfml-audio sfml-graphics sfml-window
        pod)
target_link_libraries(client-test-move-netork
        Common
        Parser
        SaltyEngine
        SFMLSaltyEngine
        ProtocolServer
        ProtocolGame
        ProtocolRoom
        dl sfml-system sfml-audio sfml-graphics sfml-window
        pod)

add_dependencies(gameserver-stable Common ProtocolServer ProtocolGame ProtocolRoom SaltyEngine SFMLSaltyEngine Parser)
add_dependencies(client-test-move-netork Common ProtocolServer ProtocolGame ProtocolRoom SaltyEngine SFMLSaltyEngine Parser prefabs)