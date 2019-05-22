//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CMAINMENU_H
#define SEMESTRALKA_CMAINMENU_H
#include "CWindow.h"

class CMainMenu : public CWindow {
public:
    void render() const;
    void processInput();
};


#endif //SEMESTRALKA_CMAINMENU_H
