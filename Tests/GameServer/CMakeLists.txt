cmake_minimum_required(VERSION 2.8)
project(rtype)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")

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
        include/Prefabs/GenericController.hpp
        Tests/GameServer/gameserver-stable.cpp)

set_target_properties(gameserver-stable PROPERTIES COMPILE_FLAGS "-DRTYPESERVER")

add_executable(client-test-move-netork
        ${Networksrc} ${Networkinc}
        ${Commoninc}
        ${Protocolsrc} ${Protocolinc}
        ${SaltyEngineinc}
        ${srcGameClient} ${incGameClient}
        ${srcGameCommon} ${incGameCommon}
        ${SFMLinc}
        Tests/GameServer/main.cpp)

#target_link_libraries(gameserv-1 -ldl)
#target_link_libraries(gameserv-2 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so)
#target_link_libraries(gameclient-1 -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so)
target_link_libraries(gameserver-stable -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so ${CMAKE_SOURCE_DIR}/lib/libParser.so)
target_link_libraries(client-test-move-netork -ldl libsfml-system.so libsfml-audio.so libsfml-graphics.so libsfml-window.so -L${CMAKE_SOURCE_DIR}/lib/ -lSaltyEngine ${CMAKE_SOURCE_DIR}/lib/libSFMLSaltyEngine.so ${CMAKE_SOURCE_DIR}/lib/libParser.so)