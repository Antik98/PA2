//
// Created by David Pham on 5/23/2019.
//

#include "CHumanPlayer.h"

CHumanPlayer::CHumanPlayer(bool loadFromSave, CardDatabase& stash) {
    if(loadFromSave){

    }else{
        deck.generateRand(stash, 0);
        hand.generateRand(stash, 1);
    }
}

int CHumanPlayer::play() {

    return 0;
}

int CHumanPlayer::takeHit() {
    return 0;
}
