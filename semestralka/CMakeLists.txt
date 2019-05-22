cmake_minimum_required(VERSION 3.13)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)

add_executable(semestralka main.cpp CBoard.cpp CBoard.h CPauseMenu.cpp CPauseMenu.h CMainMenu.cpp CMainMenu.h CGame.cpp CGame.h CWindow.cpp CWindow.h)