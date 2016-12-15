cmake_minimum_required(VERSION 2.8)
project(rtype)

file(GLOB TEST_SOURCE "Tests/GUI/*.cpp")

include_directories(include)
link_directories(../../lib)

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

	#Set Output Directories
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

	#Create library
	add_executable(gui ${TEST_SOURCE})

	#Link libraries
	target_link_libraries(gui SaltyEngine SFMLSaltyEngine Parser pthread dl sfml-system sfml-window sfml-graphics sfml-audio)

#Windows
elseif(MSVC)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	#Create library
	add_executable(gui ${TEST_SOURCE})

	#Link libraries
	target_link_libraries(gui SaltyEngine SFMLSaltyEngine Parser sfml-system sfml-window sfml-graphics sfml-audio)
endif()



#add_definitions(-DCUSTOM_ASSET_PATH="../Assets")




