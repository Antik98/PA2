//
// Created by David Pham on 5/23/2019.
//

#include "CAIPlayer.h"
using namespace std;

CAIPlayer::CAIPlayer(bool loadFromSave, CardDatabase & stash) {
    if(loadFromSave){//TODO: Save processing

    }else{
        deck.generateRand(stash, 0);
        hand.generateRand(stash, 1);
    }
}
