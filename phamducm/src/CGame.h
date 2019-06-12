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

/**
 * Main game class
 * Contains 3 main parts
 * Players - Allocated CPlayer with decks Be it AI/Player
 * Windows - Allocated CWindow* CMainMenu, CPauseMenu, CBoard in respective order
 * Database - Initialized in constructor - used as reference
 */
class CGame {
public:
    /**
     * CGame() - Constructor, generates usable CWindows, also initializes CardDatabase for use as a reference
     */
    CGame();
    ~CGame();
    /**
     * start() - main game method, contains main game loop using gameActive parameter
     * @return 0 if successful
     */
    int start();
    /**
     * save() - saves game into saveFolder/saveFile
     * @return 0 if successful, 1 if unsuccessful
     */
    bool save();
    /**
     * load() - loads game from save directory
     * @return 0 if successful, 1 if unsuccessful
     */
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
