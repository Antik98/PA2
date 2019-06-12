//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CPAUSEMENU_H
#define SEMESTRALKA_CPAUSEMENU_H
#include "CWindow.h"

/**
 * Child class of super class CWindow
 * render() - renders out choices for Menu
 */
class CPauseMenu : public CWindow{
public:
    CPauseMenu();
    ~CPauseMenu()= default;
    void render() const;
    /**
     * parseInput() - parses chosen choices
     * @return 1- Back to Game, 2- Save Game, 3- Quit Game
     */
    int parseInput();
};


#endif //SEMESTRALKA_CPAUSEMENU_H
