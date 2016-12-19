cmake_minimum_required(VERSION 2.8)
project(rtype)

#include files
include_directories(include)

#C++ files
file(GLOB ParserSrc "src/Parser/*.cpp")

#Hpp files
file(GLOB ParserInc "include/Parser/*.hpp")

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -fPIC")

	#Create library
	add_library(Parser SHARED ${ParserSrc} ${ParserInc})

#Windows
elseif(MSVC)
    
	#Include
	include_directories("include ../../Dependencies/Boost/Win/include")

	#C++FLAGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	#Create library
	add_library(Parser SHARED ${ParserSrc} ${ParserInc})

endif()