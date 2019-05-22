//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CPAUSEMENU_H
#define SEMESTRALKA_CPAUSEMENU_H
#include "CWindow.h"

class CPauseMenu : public CWindow{
public:
    CPauseMenu();
    ~CPauseMenu();
    void render() const;
    void processInput();
};


#endif //SEMESTRALKA_CPAUSEMENU_H
