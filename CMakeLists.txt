cmake_minimum_required(VERSION 3.10)

# set the project name
project(xcpp)
set(CMAKE_CONFIGURATION_TYPES release debug)

set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED   ON)
set(Boost_USE_STATIC_RUNTIME  ON)

find_package(Boost REQUIRED COMPONENTS
		system date_time filesystem regex program_options)

# add the executable
add_executable(xcpp src/main.cpp)

target_link_libraries(xcpp Boost::boost Boost::program_options)

if (WIN32)
	set_target_properties(xcpp PROPERTIES
		COMPILE_OPTIONS "$<$<CONFIG:Debug>:/MTd>;$<$<CONFIG:Release>:/MT>;/std:c++17;/MP"
	)
endif()