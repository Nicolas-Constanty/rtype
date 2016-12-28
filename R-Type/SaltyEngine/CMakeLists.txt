cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ files
	file(GLOB SaltyEngineSrc
			"src/SaltyEngine/*.cpp"
			"src/SaltyEngine/GUI/*.cpp"
			"src/SaltyEngine/Input/*.cpp"
			)

	#Hpp files
	file(GLOB SaltyEngineInc
			"include/SaltyEngine/*.hpp"
			"include/SaltyEngine/GUI/*.hpp"
			"include/SaltyEngine/Input/*.hpp"
			)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#Create library
	add_library(SaltyEngine SHARED ${SaltyEngineSrc} ${SaltyEngineInc})

	#Link libraries
	target_link_libraries(SaltyEngine Common)

#Windows
elseif(MSVC)

	#C++ files
	file(GLOB SaltyEngineSrc
		"../../src/SaltyEngine/*.cpp"
		"../../src/SaltyEngine/GUI/*.cpp"
		"../../src/SaltyEngine/Input/*.cpp"
	)

	#Hpp files
	file(GLOB SaltyEngineInc
		"../../include/SaltyEngine/*.hpp"
		"../../include/SaltyEngine/GUI/*.hpp"
		"../../include/SaltyEngine/Input/*.hpp"
	)

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#C++ FLAGS
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES -DBUILD_SHARED_LIBS -DEXPORT_LIB -DEXPORT_PREF")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNO_EXPORT")

	#Create library
	add_library(SaltyEngine STATIC ${SaltyEngineSrc} ${SaltyEngineInc})

	#Link libraries
	target_link_libraries(SaltyEngine Common)
endif()

add_dependencies(SaltyEngine Common)