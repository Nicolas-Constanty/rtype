cmake_minimum_required(VERSION 2.8)
project(rtype)

include_directories("include")

file(GLOB SRC_PROTOCOL_GAME "src/Protocol/Game/*.cpp")
file(GLOB INCLUDE_PROTOCOL_GAME "include/Protocol/Game/*.hpp")

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(ProtocolGame SHARED ${SRC_PROTOCOL_GAME} ${INCLUDE_PROTOCOL_GAME})

#Windows
elseif(MSVC)

	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DNOMINMAX -D_WINSOCK_DEPRECATED_NO_WARNINGS -DWIN32_LEAN_AND_MEAN")

	#Create library
	add_library(ProtocolGame SHARED ${SRC_PROTOCOL_GAME} ${INCLUDE_PROTOCOL_GAME})

	#Link libraries
	target_link_libraries(ProtocolGame wsock32 ws2_32)

endif()