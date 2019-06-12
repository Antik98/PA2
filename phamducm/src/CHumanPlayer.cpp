//
// Created by David Pham on 5/23/2019.
//

#include "CHumanPlayer.h"
using namespace std;

CHumanPlayer::CHumanPlayer(bool loadFromSave, CardDatabase& stash) {
    if(loadFromSave){//TODO: Save processing

    }else{
        deck.generateRand(stash, 0);
        hand.generateRand(stash, 1);
    }
}


