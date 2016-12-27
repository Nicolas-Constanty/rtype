cmake_minimum_required(VERSION 2.8)
project(rtype)

#C++ files
file(GLOB SFMLSaltyEngineSrc "src/SaltyEngine/SFML/*.cpp")

#Hpp files
file(GLOB SFMLSaltyEngineInc "include/SaltyEngine/SFML/*.hpp")

#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output directory
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")


	#Create library
	add_library(SFMLSaltyEngine SHARED ${SFMLSaltyEngineSrc} ${SFMLSaltyEngineInc})

	#Link libraries
	target_link_libraries(SFMLSaltyEngine Common Parser SaltyEngine sfml-system sfml-window sfml-graphics sfml-audio)
#Windows
elseif(MSVC)

	#Export all symbol for dll
	#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#Create library
	add_library(SFMLSaltyEngine STATIC ${SFMLSaltyEngineSrc})

	#Link libraries
	target_link_libraries(SFMLSaltyEngine Common Parser SaltyEngine sfml-system sfml-window sfml-graphics sfml-audio)
endif()

add_dependencies(SFMLSaltyEngine SaltyEngine)