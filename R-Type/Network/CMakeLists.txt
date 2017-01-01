cmake_minimum_required(VERSION 2.8)
project(rtype)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	file(GLOB NETWORK_SRC src/Network/*/*.cpp)
	file(GLOB NETWORK_INCLUDE include/Network/*/*.hpp)
	
	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(Network SHARED ${NETWORK_SRC} ${NETWORK_INCLUDE})

#Windows
elseif(MSVC)

	file(GLOB NETWORK_SRC "../../src/Network/*/*.cpp")

	file(GLOB NETWORK_INCLUDE "../../include/Network/*/*.hpp" "../../include/Network/*.hpp")

	

	if(EXPORT_DLL)
		#Export all symbol for dll
		set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

		#C++ FLAGS
		#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DBUILD_SHARED_LIBS -DEXPORT_LIB -DEXPORT_PREF")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DNO_EXPORT")
		
		#Create library
		add_library(Network SHARED ${NETWORK_SRC} ${NETWORK_INCLUDE})
	else()
		#C++ FLAGS
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DNO_EXPORT")
	
		#Create library
		add_library(Network STATIC ${NETWORK_SRC} ${NETWORK_INCLUDE})
	endif()

	#Link libraries
	target_link_libraries(Network wsock32 ws2_32)

endif()