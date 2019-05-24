//
// Created by David Pham on 5/22/2019.
//
#include <iostream>
#include <fstream>
#include <set>
#include "CCardStack.h"



using namespace std;
class incorrectUseOfCCardStackConstructor{};
class databaseNotInitializedProperly{};

bool generateDeck(CardDatabase& stash, CCardStack& stack, int amount){
    set<int> addedOnce;
    set<int> addedTwice;

    for(int i = 0; i<amount;){
        int index= rand()%databaseAmount;
        if(addedOnce.find(index)==addedOnce.end()){
            stack.deck.push_back(stash.database.at(index));
            addedOnce.insert(index);
            i++;
        }else if(addedTwice.find(index)==addedTwice.end()){
            stack.deck.push_back(stash.database.at(index));
            addedTwice.insert(index);
            i++;
        }else{
            continue;
        }
    }
    return true;
}

CCardStack::CCardStack() = default;


int CCardStack::loadSave(CardDatabase & database, string& fileName) {
    ifstream inputFile;
    inputFile.open(fileName);

    return 0;
}

int CCardStack::generateRand(CardDatabase & stash, bool isHand) {
    deck.clear();
    if(stash.database.size()!=databaseAmount-1)
        throw databaseNotInitializedProperly();

    if(isHand){
        generateDeck(stash, *this, handAmount);
    }else{
        generateDeck(stash, *this, deckAmount);
    }

    return 0;
}
