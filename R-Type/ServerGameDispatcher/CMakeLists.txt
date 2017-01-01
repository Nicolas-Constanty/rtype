cmake_minimum_required(VERSION 2.8)
project(rtype)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	file(GLOB serverGameDispatcherSrc "src/Thread/*.cpp" "src/Process/*.cpp" "src/ServerGame/CreateRoomGameServer/*.cpp")

	file(GLOB serverGameDispatcherInc "include/Thread/*.hpp" "include/Process/*.hpp" "include/ServerGame/CreateRoomGameServer/*.hpp" "include/Common/*.hpp")

	add_executable(RoomGameDispatcher ${serverGameDispatcherSrc} ${serverGameDispatcherInc})

	target_link_libraries(RoomGameDispatcher Network ProtocolGame ProtocolServer ProtocolRoom dl pthread Common)
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	file(GLOB serverGameDispatcherSrc "../../src/Thread/*.cpp" "../../src/Process/*.cpp" "../../src/ServerGame/CreateRoomGameServer/*.cpp")

	file(GLOB serverGameDispatcherInc "../../include/Thread/*.hpp" "../../include/Process/*.hpp" "../../include/ServerGame/CreateRoomGameServer/*.hpp ../../include/Common/*.hpp")

	add_executable(RoomGameDispatcher ${serverGameDispatcherSrc} ${serverGameDispatcherInc})

	target_link_libraries(RoomGameDispatcher Network ProtocolGame ProtocolServer ProtocolRoom pthread Common)
endif()