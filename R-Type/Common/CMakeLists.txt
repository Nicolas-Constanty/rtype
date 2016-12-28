cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ files
	file(GLOB Commoninc include/Common/*.hpp)

	#Hpp files
	file(GLOB Commonsrc src/Common/*.cpp)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(Common SHARED ${Commonsrc} ${Commoninc})

#Windows
elseif(MSVC)

	#C++ files
	file(GLOB Commoninc "../../include/Common/*.hpp")

	#Hpp files
	file(GLOB Commonsrc "../../src/Common/*.cpp")

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_EXPORT")

	#Create library
	add_library(Common STATIC ${Commonsrc} ${Commoninc})

endif()