cmake_minimum_required(VERSION 3.12)
project(chludil)

set(CMAKE_CXX_STANDARD 14)

add_executable(chludil main.cpp, chludil pushpop.cpp, chludil pushpop.h)