cmake_minimum_required(VERSION 2.8)
project(rtype)




#Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_POSITION_INDEPENDENT_CODE ON)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -rdynamic")

	#include files
	include_directories("include")

	#C++ files
	file(GLOB SOURCE_SALTYENGINE_FILE
        "src/SaltyEngine/*.cpp"
        "src/SaltyEngine/GUI/*.cpp"
        "src/SaltyEngine/Input/*.cpp"
        "src/Common/LibLoader.cpp"
		"src/Common/Debug.cpp"
        )

	#Create library
	add_library(SaltyEngine SHARED ${SOURCE_SALTYENGINE_FILE})

#Windows
elseif(MSVC)

	#Export all symbol for dll
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

	#Set Output Directories
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}../../lib)

	#C++ FLAGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES")

	#C++ files
	file(GLOB SOURCE_SALTYENGINE_FILE
        "src/SaltyEngine/*.cpp"
        "src/SaltyEngine/GUI/*.cpp"
        "src/SaltyEngine/Input/*.cpp"
        "src/Common/DllLoader.cpp"
		"src/Common/Debug.cpp"
		)

	#Create library
	add_library(SaltyEngine STATIC ${SOURCE_SALTYENGINE_FILE})

endif()



