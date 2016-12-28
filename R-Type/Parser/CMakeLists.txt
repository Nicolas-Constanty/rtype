cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ files
	file(GLOB ParserSrc "src/Parser/*.cpp")

	#Hpp files
	file(GLOB ParserInc "include/Parser/*.hpp")

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -fPIC")

	#Create library
	add_library(Parser SHARED ${ParserSrc} ${ParserInc})

#Windows
elseif(MSVC)

	#C++ files
	file(GLOB ParserSrc "../../src/Parser/*.cpp")

	#Hpp files
	file(GLOB ParserInc "../../include/Parser/*.hpp")
	if(EXPORT_DLL)
		set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_EXPORT")

		#Create library
		add_library(Parser SHARED ${ParserSrc})
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_EXPORT")

		#Create library
		add_library(Parser STATIC ${ParserSrc})
	endif()

endif()