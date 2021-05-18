cmake_minimum_required(VERSION 3.20)
project(TestRequestParser)
enable_testing()
#add_subdirectory(${GMOCK_ROOT})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include_directories(${GMOCK_ROOT}/include)
include_directories(${GMOCK_ROOT}/gtest/include)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(./src/Header)

set (CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

add_executable(TestRequestParser 
				src/Implement/UnitTestRequestParser.cpp
				src/Implement/RequestParser.cpp
				#src/Implement/Operat.cpp
				src/Header/RequestParser.h
				src/Header/OperateData.h
				)
target_link_libraries(TestRequestParser pthread GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)