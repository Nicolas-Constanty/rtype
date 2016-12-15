cmake_minimum_required(VERSION 2.8)
project(rtype)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

add_executable(serverRoom
        ${Networksrc} ${Networkinc}
        ${Commoninc} ${Commonsrc}
        ${Protocolsrc} ${Protocolinc}
        ${serverRoomsrc} ${serverRoominc}
        src/ServerRoom/main.cpp)

target_link_libraries(serverRoom ldl)