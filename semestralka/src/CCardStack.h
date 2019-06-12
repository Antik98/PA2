//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARDSTACK_H
#define SEMESTRALKA_CCARDSTACK_H

#include <iostream>
#include <vector>
#include "CCard.h"
#include "CardDatabase.h"
#include "CBoard.h"

//id in database also correspond to index in vector

static const int handAmount = 3;
static const int maxHandAmount = 7;
static const int deckAmount = 25;

class CCardStack {
public:
    CCardStack();// random
    void render() const;
    bool loadSave(CardDatabase& database, std::string&);
    bool loadSaveBoard(CardDatabase& database, std::string&);
    int generateRand(CardDatabase&, bool isHand);// generates random set of cards from database
    friend bool generateDeck(CardDatabase& stash, CCardStack& deck,  int amount);
    friend class CBoard;
    friend class CPlayer;
    friend class CGame;
    friend int chooseTarget(CGame* gamePtr, int playerIndex);
    friend int attack(CGame* gamePtr, int damage);
    friend int attackAI(CGame* gamePtr, int damage);
private:
    std::vector<CCard*> deck;
};

#endif //SEMESTRALKA_CCARDSTACK_H
