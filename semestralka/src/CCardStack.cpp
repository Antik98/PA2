//
// Created by David Pham on 5/22/2019.
//
#include <iostream>
#include <fstream>
#include <set>
#include <random>
#include <sstream>
#include "CCardStack.h"
#include "CMinion.h"


using namespace std;
class incorrectUseOfCCardStackConstructor{};
class databaseNotInitializedProperly{};

bool generateDeck(CardDatabase& stash, CCardStack& stack, int amount){
    set<int> addedOnce;
    set<int> addedTwice;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> randomIndex(0,databaseAmount-1);

    for(int i = 0; i<amount;){
        int index= randomIndex(rng);
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


bool CCardStack::loadSave(CardDatabase & database, string& deckString) {
    istringstream iss;
    iss.str(deckString);
    int potentialId=0;
    do{
        int potentialId=0;
        iss >> potentialId;
        if(potentialId>=0 && potentialId<=32){
            deck.push_back(database.database[potentialId]);
        }else{
            return false;
        }
    }while(iss.good());

    return true;
}

bool CCardStack::loadSaveBoard(CardDatabase & database, string& deckString) {
    istringstream iss;
    iss.str(deckString);
    int potentialId=0;
    do{
        int potentialId=0;
        char dummy;
        int potentialHP=0;
        iss >> potentialId >> dummy >> potentialHP;
        if(potentialId>=0 && potentialId<=32 && dummy==':' && potentialHP>0){
            CCard* temp = database.database[potentialId]->clone();
            temp->setHP(potentialHP);
            deck.push_back(temp);
        }else{
            return false;
        }
    }while(iss.good());

    return true;
}

int CCardStack::generateRand(CardDatabase & stash, bool isHand) {
    deck.clear();
    if(stash.database.size()!=databaseAmount)
        throw databaseNotInitializedProperly();

    if(isHand){
        generateDeck(stash, *this, handAmount);
    }else{
        generateDeck(stash, *this, deckAmount);
    }

    return 0;
}

void CCardStack::render() const{

    if (deck.size()) {
        for(int i =0; i<deck.size(); i++){
            cout << "   [" << i << "] ";
            deck.at(i)->render();
        }
    }else{
        cout << "   *** Board Empty ***" << endl;
    }

}
