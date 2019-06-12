cmake_minimum_required(VERSION 3.14)
project(semestralka)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(semestralka
        CBoard.cpp
        CBoard.h
        CGame.cpp
        CGame.h
        CMainMenu.cpp
        CMainMenu.h
        CPauseMenu.cpp
        CPauseMenu.h
        CWindow.cpp
        CWindow.h
        main.cpp CCardStack.cpp CCardStack.h CCard.cpp CCard.h CMinion.cpp CMinion.h CSpell.cpp CSpell.h CardDatabase.cpp CardDatabase.h CPlayer.cpp CPlayer.h CHumanPlayer.cpp CHumanPlayer.h CAIPlayer.cpp CAIPlayer.h)
