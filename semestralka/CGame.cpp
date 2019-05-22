//
// Created by David on 17.05.2019.
//

#include "CGame.h"
#include "CMainMenu.h"
#include "CPauseMenu.h"

CGame::CGame() {
    windows.push_back(new CMainMenu());
    windows.push_back(new CPauseMenu())
    windows.push_back(new CBoard());
}

CGame::~CGame() {

}
