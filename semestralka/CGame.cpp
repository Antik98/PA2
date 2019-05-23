//
// Created by David on 17.05.2019.
//

#include "CGame.h"
#include "CMainMenu.h"
#include "CPauseMenu.h"

CGame::CGame() {
    windows.push_back(new CMainMenu());
    windows.push_back(new CPauseMenu());
   // windows.push_back(new CBoard());
}

CGame::~CGame() {

}

int CGame::start() {
    activeWindowIndex=0;
    windows[activeWindowIndex]->render();
    int mainMenuSelection= windows[activeWindowIndex]->parseInput();

    switch (mainMenuSelection){
        case 1:{ // start new game

        }
        case 2:{ // load a game

        }
        case 3:{
            return 0;
        }
    }

}
