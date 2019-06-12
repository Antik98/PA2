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


/**
 * CCardStack
 * Used as container for CCards, also has load mechanism for Load Game
 */
class CCardStack {
public:
    CCardStack();// random
    /**
     * Pure visual function, used for CHumanPlayer
     */
    void render() const;
    /**
     * Loads contents of previous save CHand, CDeck
     * @param database database generated at beginning
     * @return true if successful
     */
    bool loadSave(CardDatabase& database, std::string&);
    /**
     * Loads contents of previous save CBoard
     * @param database database generated at beginning
     * @return true if successful
     */
    bool loadSaveBoard(CardDatabase& database, std::string&);
    /**
     * Helper function for generate Rand
     * @param isHand - true if generating for CHand
     * @return 0 if successful
     */
    int generateRand(CardDatabase&, bool isHand);// generates random set of cards from database
    /**
     * Generates random deck
     * @param amount - Amount of cards needed for specific deck
     * @return
     */
    friend bool generateDeck(CardDatabase& , CCardStack& ,  int amount);
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
