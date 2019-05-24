//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CPLAYER_H
#define SEMESTRALKA_CPLAYER_H


#include <iostream>
#include "CCardStack.h"
using namespace std;

class CPlayer {
protected:
    int hp=30;
    CCardStack board;
    CCardStack hand;
    CCardStack deck;
public:
    virtual int play()=0;
    virtual int takeHit()=0;
};


#endif //SEMESTRALKA_CPLAYER_H
