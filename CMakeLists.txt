cmake_minimum_required(VERSION 3.16)
project(TestRequestParser)
set (CMAKE_CXX_STANDARD 11)
find_package(GTest CONFIG REQUIRED)
include_directories(
	./src/Header
	./src/UnitTest/include
)

add_executable(TestRequestParser 
				src/Implement/UnitTestRequestParser.cpp
				src/Implement/RequestParser.cpp
				src/Header/RequestParser.h)
target_link_libraries(TestRequestParser pthread)
