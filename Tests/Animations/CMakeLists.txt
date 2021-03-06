cmake_minimum_required(VERSION 2.8)
project(rtype)

include_directories(include)

file(GLOB TEST_SOURCE "Tests/Animations/*.cpp" "src/Rtype/Game/Client/BackgroundController.cpp")


#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

	#Create library
	add_executable(test_animations ${TEST_SOURCE})

	#Link libraries
	target_link_libraries(test_animations Common SaltyEngine SFMLSaltyEngine Parser pthread dl sfml-system sfml-window sfml-graphics sfml-audio)

#Windows
elseif(MSVC)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

	#Create library
	add_executable(test_animations ${TEST_SOURCE})

	#Link libraries
	target_link_libraries(test_animations Common SaltyEngine SFMLSaltyEngine Parser sfml-system sfml-window sfml-graphics sfml-audio)
endif()

add_dependencies(test_animations SFMLSaltyEngine)