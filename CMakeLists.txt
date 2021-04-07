# Copyright (c) 2021, 鍾淯丞, 周杰仕, 林仁鴻. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

cmake_minimum_required(VERSION 3.10)
project(AllTest)
enable_testing()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories(${GMOCK_ROOT}/include)
include_directories(${GMOCK_ROOT}/gtest/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Header)
message(STATUS ${GMOCK_ROOT})
find_package(GTest REQUIRED)

include(GoogleTest)

if(UNIX)
#TODO: will be remove after All UnitTest version is completed
# cmake 3.16 link library is different from 3.20
#	add_executable(TestRequestParser 
#			src/Implement/UnitTestRequestParser.cpp
#			src/Implement/RequestParser.cpp
#			src/Header/RequestParser.h
#			src/Header/OperateData.h
#			src/Implement/OperateData.cpp
#			)
#	target_link_libraries(TestRequestParser pthread GTest::GTest GTest::Main)# GTest::gmock GTest::gmock_main)
#	gtest_discover_tests(TestRequestParser)
#	add_test(RequestParser_test TestRequestParser)

#	add_executable(TestHttpListener 
#			src/Implement/UnitTestHttpListener.cpp
#			src/Implement/HttpListener.cpp
#			src/Header/HttpListener.h
#			)
#	target_link_libraries(TestHttpListener pthread GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#	gtest_discover_tests(TestHttpListener)
#	add_test(HttpListener_test TestHttpListener)

#	add_executable(TestRequestHandler 
#			src/Implement/UnitTestRequestHandler.cpp
#			src/Implement/RequestParser.cpp
#			src/Header/RequestParser.h
#			src/Implement/RequestHandler.cpp
#			src/Header/RequestHandler.h
#			src/Header/OperateData.h
#			)
#	target_link_libraries(TestRequestHandler pthread GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
#	gtest_discover_tests(TestRequestHandler)
#	add_test(RequestHandler_test TestRequestHandler)

# Will remove comment after all file is ready
add_executable(UnitTest 
# Made by younger15
#			src/Implement/UnitTestRequestHandler.cpp
#			src/Implement/UnitTestMainManager.cpp
#			src/Implement/UnitTestHttpListener.cpp
			src/Implement/UnitTestRequestParser.cpp
			src/Header/RequestParser.h
			src/Implement/RequestParser.cpp
			src/Header/OperateData.h
			src/Implement/OperateData.cpp
#			src/Implement/UnitTestAuthenticator.cpp
# Made by Jazz
#			src/Implement/UnitTestOperateData.cpp
#			src/Implement/UnitTestErrorHandle.cpp
#			src/Implement/UnitTestDownloadStream.cpp
#			src/Implement/UnitTestUploadStream.cpp
# Made by Hong
#			src/Implement/UnitTestResponseParser.cpp
#			src/Implement/UnitTestResponseHandler.cpp
#			src/Implement/UnitTestResponseEncoder.cpp
#			src/Implement/UnitTestFileOperator.cpp
			)
# command between 3.16 and 3.20 for gtest is different
if(CMAKE_MINOR_VERSION LESS 20})
target_link_libraries(UnitTest pthread GTest::GTest GTest::Main)
else()
target_link_libraries(UnitTest pthread GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
endif()
gtest_discover_tests(UnitTest)
add_test(UnitTest_test UnitTest)
else()
message( FATAL_ERROR "must be Linux based OS")
endif()

