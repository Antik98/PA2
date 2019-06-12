//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CAIPLAYER_H
#define SEMESTRALKA_CAIPLAYER_H


#include <iostream>
#include "CPlayer.h"


class CAIPlayer : public CPlayer {
public:
    CAIPlayer(bool loadFromSave, CardDatabase&);
};


#endif //SEMESTRALKA_CAIPLAYER_H
