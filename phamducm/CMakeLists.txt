cmake_minimum_required(VERSION 3.14)
project(phamducm)

set(CMAKE_CXX_STANDARD 14)

include_directories(semestralka/src)
include_directories(src)

add_executable(phamducm
        src/CAIPlayer.cpp
        src/CAIPlayer.h
        src/CardDatabase.cpp
        src/CardDatabase.h
        src/CBoard.cpp
        src/CBoard.h
        src/CCard.cpp
        src/CCard.h
        src/CCardStack.cpp
        src/CCardStack.h
        src/CGame.cpp
        src/CGame.h
        src/CHumanPlayer.cpp
        src/CHumanPlayer.h
        src/CMainMenu.cpp
        src/CMainMenu.h
        src/CMinion.cpp
        src/CMinion.h
        src/CPauseMenu.cpp
        src/CPauseMenu.h
        src/CPlayer.cpp
        src/CPlayer.h
        src/CSpell.cpp
        src/CSpell.h
        src/CWindow.cpp
        src/CWindow.h
        src/main.cpp)
