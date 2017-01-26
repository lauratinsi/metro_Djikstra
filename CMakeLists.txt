cmake_minimum_required(VERSION 3.6)
project(metro_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp nodes.cpp nodes.h vecnodes.cpp vecnodes.h station.cpp station.h)
add_executable(metro_2 ${SOURCE_FILES})