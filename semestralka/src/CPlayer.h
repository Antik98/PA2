//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CPLAYER_H
#define SEMESTRALKA_CPLAYER_H


#include <iostream>
#include "CCardStack.h"

class CPlayer {
protected:
    int hp=30;
    int availableMana=10;
    CCardStack hand;
    CCardStack deck;
public:
    CPlayer();
    virtual ~CPlayer();
    CCardStack board;
    bool isAlive = true;
    virtual int takeHit(int damage);
    friend class CCardStack;
    friend class CBoard;
    friend class CGame;
};


#endif //SEMESTRALKA_CPLAYER_H
