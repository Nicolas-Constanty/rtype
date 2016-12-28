cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	
	file(GLOB SRC_PROTOCOL_SERVER "src/Protocol/Server/*.cpp")
	file(GLOB INCLUDE_PROTOCOL_SERVER "src/Protocol/Server/*.hpp")
	
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(ProtocolServer SHARED ${SRC_PROTOCOL_SERVER} ${INCLUDE_PROTOCOL_SERVER})

#Windows
elseif(MSVC)

	file(GLOB SRC_PROTOCOL_SERVER "../../../src/Protocol/Server/*.cpp")

	file(GLOB INCLUDE_PROTOCOL_SERVER "../../../src/Protocol/Server/*.hpp")

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DNOMINMAX -D_WINSOCK_DEPRECATED_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -DNO_EXPORT")

	#Create library
	add_library(ProtocolServer STATIC ${SRC_PROTOCOL_SERVER} ${INCLUDE_PROTOCOL_SERVER})

	#Link libraries
	target_link_libraries(ProtocolServer wsock32 ws2_32)

endif()