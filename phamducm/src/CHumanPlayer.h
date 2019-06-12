//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CHUMANPLAYER_H
#define SEMESTRALKA_CHUMANPLAYER_H


#include <iostream>
#include "CPlayer.h"

/**
 * Child Class to Cplayer
 * CHumanPlayer() - Constructor generates set of cards from received database and
 * sets default values for HP and mana
 * decks are blank in preparation for loading if necessary
 */
class CHumanPlayer : public CPlayer {
public:
    CHumanPlayer(bool loadFromSave, CardDatabase&);
};


#endif //SEMESTRALKA_CHUMANPLAYER_H
