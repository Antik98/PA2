//
// Created by David on 17.05.2019.
//

#include "CGame.h"
#include "CMainMenu.h"
#include "CPauseMenu.h"
#include "CHumanPlayer.h"
#include "CAIPlayer.h"

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
        case 1:{ // start new game - PvP
            players.push_back(new CHumanPlayer(false, database));
            players.push_back(new CHumanPlayer(false, database));
        }
        case 2:{ // start new game - PvAI
            players.push_back(new CAIPlayer());
            players.push_back(new CHumanPlayer());
        }
        case 3:{ // load game

        }
        case 4:{ // exit
            return 0;
        }
    }
return 0;
}
