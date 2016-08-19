
cmake_minimum_required(VERSION 3.5)
project(Cube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES global.h main.cpp cube.cpp cube.h tester.cpp tester.h)
add_executable(Cube ${SOURCE_FILES})