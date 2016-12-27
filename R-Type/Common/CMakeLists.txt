cmake_minimum_required(VERSION 2.8)
project(rtype)

#include files
include_directories("include")

#C++ files
file(GLOB Commoninc include/Common/*.hpp)

#Hpp files
file(GLOB Commonsrc src/Common/*.cpp)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(Common SHARED ${Commonsrc} ${Commoninc})

#Windows
elseif(MSVC)

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#Create library
	add_library(Common STATIC ${Commonsrc} ${Commoninc})

endif()