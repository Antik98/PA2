//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CGAME_H
#define SEMESTRALKA_CGAME_H

#include <vector>
#include "CardDatabase.h"
#include "CMainMenu.h"
#include "CPauseMenu.h"
#include "CBoard.h"
#include "CHumanPlayer.h"
#include "CAIPlayer.h"

class CGame {
public:
    CGame();
    ~CGame();
    int start();
    bool save();
    bool load();
    friend class CBoard;
    friend int chooseTarget(CGame* gamePtr, int playerIndex);
    friend int attack(CGame* gamePtr, int damage);
    friend int attackAI(CGame* gamePtr, int damage);
protected:
    bool gameActive;
    bool isAIGame;
    bool gameLoaded;
    int activePlayerIndex;
    int activeWindowIndex;
    std::vector<CWindow*> windows;
    CardDatabase database;
    std::vector<CPlayer*> players;
};


#endif //SEMESTRALKA_CGAME_H
