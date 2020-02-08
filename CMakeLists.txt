cmake_minimum_required(VERSION 3.10)

# set the project name
project(xcpp)
set(CMAKE_CONFIGURATION_TYPES release debug)
# add the executable
add_executable(xcpp src/main.cpp)


if (WIN32)
	set_target_properties(xcpp PROPERTIES
		COMPILE_OPTIONS "$<$<CONFIG:Debug>:/MTd>;$<$<CONFIG:Release>:/MT>;/std:c++17;/MP"
	)
endif()