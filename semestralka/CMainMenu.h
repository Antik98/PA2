//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CMAINMENU_H
#define SEMESTRALKA_CMAINMENU_H
#include "CWindow.h"

class CMainMenu : public CWindow {
public:
    CMainMenu()=default;
    ~CMainMenu()= default;
    void render() const override;
    int parseInput();
};


#endif //SEMESTRALKA_CMAINMENU_H
