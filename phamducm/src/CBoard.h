//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CBOARD_H
#define SEMESTRALKA_CBOARD_H

#include <iostream>
#include "CWindow.h"

class CGame;

/**
 * Child class to superclass CWindow
 * Used during normal play, contains logic for the actual game
 */
class CBoard : public CWindow {
public:
    CBoard(CGame&);
    /**
     * Acts differently if used by AI/HumanPlayer
     * Render - renders out HUD for the game for the human player
     */
    void render() const override;
    /**
     * parseInput - processes input of AI/Player progressing the game
     * @return 1 player dead, 2 player change, 3 change to pause menu
     */
    int  parseInput() override;
protected:
    CGame* gamePtr;
};


#endif //SEMESTRALKA_CBOARD_H
