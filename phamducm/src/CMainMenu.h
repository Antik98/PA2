//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CMAINMENU_H
#define SEMESTRALKA_CMAINMENU_H
#include "CWindow.h"

/**
 * Child class of super class CWindow
 * render() - renders out choices for Menu
 */
class CMainMenu : public CWindow {
public:
    CMainMenu()=default;
    ~CMainMenu()= default;
    void render() const override;
    /**
     * parseInput() - parses chosen choices
     * @return 1 - Play Pvp, 2- Play PvAI, 3- Load Previous Game, 4- Exit game
     */
    int parseInput();
};


#endif //SEMESTRALKA_CMAINMENU_H
