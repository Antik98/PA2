//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CBOARD_H
#define SEMESTRALKA_CBOARD_H

#include <iostream>
#include "CWindow.h"

class CGame;


class CBoard : public CWindow {
public:
    CBoard(CGame&);
    void render() const override;
    int  parseInput() override;
protected:
    CGame* gamePtr;
};


#endif //SEMESTRALKA_CBOARD_H
