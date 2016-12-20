cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("include")

file(GLOB NETWORK_SRC src/Network/*/*.cpp)
file(GLOB NETWORK_INCLUDE include/Network/*/*.hpp)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	
	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(Network SHARED ${NETWORK_SRC} ${NETWORK_INCLUDE})

#Windows
elseif(MSVC)

	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DNOMINMAX -D_WINSOCK_DEPRECATED_NO_WARNINGS -DWIN32_LEAN_AND_MEAN")

	#Create library
	add_library(Network STATIC ${NETWORK_SRC} ${NETWORK_INCLUDE})

	#Link libraries
	target_link_libraries(Network wsock32 ws2_32)

endif()