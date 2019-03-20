cmake_minimum_required(VERSION 3.13)
project(prog1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -Wextra -pedantic")

add_executable(prog1 main.cpp)