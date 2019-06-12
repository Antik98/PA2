//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CWINDOW_H
#define SEMESTRALKA_CWINDOW_H

/**
 * Abstract Super class of CPauseMenu, CMainMenu, and CBoard
 * Has 2 main methods
 */

class CWindow {
public:
    CWindow()= default;
    virtual ~CWindow()= default;
    /**
     * render() - graphicaly shows contents of the menu, usually prints out options which are chosen by next method
     */
    virtual void render() const = 0;
    /**
     * parseInput() - method communicates with player, and continues based on user's choices
     * @return 1-4 choices depend on which polymorphic structure is used
     */
    virtual int parseInput() = 0;

};


#endif //SEMESTRALKA_CWINDOW_H
