//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CHUMANPLAYER_H
#define SEMESTRALKA_CHUMANPLAYER_H


#include <iostream>
#include "CPlayer.h"


class CHumanPlayer : public CPlayer {
public:
    CHumanPlayer(bool loadFromSave, CardDatabase&);
};


#endif //SEMESTRALKA_CHUMANPLAYER_H
