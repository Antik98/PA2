cmake_minimum_required(VERSION 3.14)
project(Semestralka)

set(CMAKE_CXX_STANDARD 14)

add_executable(Semestralka main.cpp CGame.h CGame.cpp CBoard.h CBoard.cpp)
#add_executable(Semestralka main.cpp CGame.cpp CGame.h CWindow.cpp CWindow.h CBoard.cpp CBoard.h CMenu.cpp CMenu.h CMainMenu.cpp CMainMenu.h CPauseMenu.cpp CPauseMenu.h CCard.cpp CCard.h CMinion.cpp CMinion.h CSpell.cpp CSpell.h)