cmake_minimum_required(VERSION 2.8)

file(GLOB process_sources ${PROJECT_SOURCE_DIR}/Tests/Process/*.cpp)
file(GLOB process_includes ${PROJECT_SOURCE_DIR}/Tests/Process/*.hpp)
file(GLOB depend_sources ${PROJECT_SOURCE_DIR}/src/Process/*.cpp)
file(GLOB depend_includes ${PROJECT_SOURCE_DIR}/include/Process/*.hpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

	set(CMAKE_CXX_FLAGS "-std=c++11 -W -Wall")

	add_executable(proco ${process_sources} ${process_include} ${depend_sources} ${depend_includes})

elseif(MSVC)

	add_executable(proco ${process_sources} ${depend_sources})

endif()