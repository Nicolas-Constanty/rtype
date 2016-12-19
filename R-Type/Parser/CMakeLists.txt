cmake_minimum_required(VERSION 2.8)
project(rtype)



#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -fPIC")

	#Include
	include_directories("include")

	#Compiled file
	file(GLOB SOURCE_PARSER_FILE "src/Parser/*.cpp" "include/Parser/*.hpp")

	#Create library
	add_library(Parser SHARED ${SOURCE_PARSER_FILE})

#Windows
elseif(MSVC)
    
	#Include
	include_directories("include ../../Dependencies/Boost/Win/include")

	#C++FLAGS
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	#Compiled file
	file(GLOB SOURCE_PARSER_FILE "src/Parser/*.cpp")

	#Create library
	add_library(Parser SHARED ${SOURCE_PARSER_FILE})

endif()