//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CPLAYER_H
#define SEMESTRALKA_CPLAYER_H


#include <iostream>
#include "CCardStack.h"
/**
 * Super class to CHumanPlayer and to CAIPlayer
 * class has 3 CCardStacks used throughout the game, hand, deck, and board
 * Board is normally allocated separately, hand and deck are reference to the database
 */


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
    /**
     * takeHit() - takes integer of damage applies it to its own HP value,
     * @param damage
     * @returns 1 if player dies, 0 if not
     */
    virtual int takeHit(int damage);
    friend class CCardStack;
    friend class CBoard;
    friend class CGame;
};


#endif //SEMESTRALKA_CPLAYER_H
