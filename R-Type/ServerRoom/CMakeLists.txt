cmake_minimum_required(VERSION 2.8)
project(rtype)

include_directories("include")
file(GLOB serverRoomSrc src/ServerRoom/*.cpp)
file(GLOB serverRoomInc include/ServerRoom/*.hpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

add_executable(serverRoom
        ${serverRoomSrc} ${serverRoomIrc}
        src/ServerRoom/main.cpp)

target_link_libraries(serverRoom dl Network Common ProtocolGame ProtocolServer ProtocolRoom)

add_dependencies(Network Common ProtocolGame ProtocolServer ProtocolRoom)