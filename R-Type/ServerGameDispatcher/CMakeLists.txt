cmake_minimum_required(VERSION 2.8)
project(rtype)

file(GLOB serverGameDispatcherSrc src/Thread/*.cpp src/Process/*.cpp src/ServerGame/CreateRoomGameServer/*.cpp)

file(GLOB serverGameDispatcherInc include/Thread/*.hpp include/Process/*.hpp src/ServerGame/CreateRoomGameServer/*.hpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
endif()

add_executable(serverGameDispatcher ${serverGameDispatcherSrc} ${serverGameDispatcherInc})

target_link_libraries(serverGameDispatcher Network ProtocolGame ProtocolServer ProtocolRoom dl pthread)