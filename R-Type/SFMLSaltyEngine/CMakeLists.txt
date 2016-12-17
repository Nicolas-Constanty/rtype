cmake_minimum_required(VERSION 2.8)
project(rtype)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output directory
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#include files
	include_directories(include)

	#C++ files
	file(GLOB SOURCE_SALTYENGINE_SFML_FILE "src/SaltyEngine/SFML/*.cpp")

	#Create library
	add_library(SFMLSaltyEngine SHARED ${SOURCE_SALTYENGINE_SFML_FILE})

	#Link libraries
	target_link_libraries(SFMLSaltyEngine Parser SaltyEngine sfml-system sfml-window sfml-graphics sfml-audio)

	#Add custom target
	add_custom_target(BUILD_ENGINE DEPENDS SaltyEngine SFMLSaltyEngine)
#Windows
elseif(MSVC)

	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	#include files
	include_directories("include ../../Dependencies/SFML/Win/include")

	#libraries files
	link_directories("../Dependencies/SFML/Win/x64/Release")

	#C++ files
	file(GLOB SOURCE_SALTYENGINE_SFML_FILE "src/SaltyEngine/SFML/*.cpp" "include/SaltyEngine/SFML/*.hpp")

	#Create library
	add_library(SFMLSaltyEngine SHARED ${SOURCE_SALTYENGINE_SFML_FILE} ../../src/SaltyEngine/SFML/PhysicsHandler.cpp ../../src/SaltyEngine/SFML/BoxCollider2D.cpp)

	#Link libraries
	target_link_libraries(SFMLSaltyEngine Parser SaltyEngine sfml-system sfml-window sfml-graphics sfml-audio)

endif()


