cmake_minimum_required(VERSION 2.8)
project(rtype)

include_directories("include")
file(GLOB serverRoomSrc src/ServerRoom/*.cpp)
file(GLOB serverRoomInc include/ServerRoom/*.hpp)

add_executable(RoomServer
        ${serverRoomSrc} ${serverRoomIrc}
        src/ServerRoom/main.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")
	target_link_libraries(RoomServer dl Network Common ProtocolGame ProtocolServer ProtocolRoom)
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
	target_link_libraries(RoomServer Network Common ProtocolGame ProtocolServer ProtocolRoom)
endif()

add_dependencies(Network Common ProtocolGame ProtocolServer ProtocolRoom)