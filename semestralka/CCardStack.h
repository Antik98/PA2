//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARDSTACK_H
#define SEMESTRALKA_CCARDSTACK_H

#include <iostream>
#include <vector>
#include "CCard.h"
#include "CardDatabase.h"
using namespace std;
//id in database also correspond to index in vector

static const int handAmount = 5;
static const int deckAmount = 20;


class CCardStack {
public:
    CCardStack();// random
    int loadSave(CardDatabase& database, string& fileName);
    int generateRand(CardDatabase&, bool isHand);// generates random set of cards from database
    friend bool generateDeck(CardDatabase& stash, CCardStack& deck,  int amount);
protected:
    vector<CCard*> deck;
};


#endif //SEMESTRALKA_CCARDSTACK_H
