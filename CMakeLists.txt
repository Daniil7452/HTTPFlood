cmake_minimum_required(VERSION 3.5)

project(HTTPFlood)

find_package(Boost REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost.")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(Connection FifoQueue)

add_executable(main main.cpp)

add_subdirectory(FifoQueue)
target_link_libraries(main FifoQueue)

add_subdirectory(Connection)
target_link_libraries(main Connection)

