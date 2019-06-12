//
// Created by David Pham on 5/23/2019.
//

#include "CPlayer.h"

int CPlayer::takeHit(int damage) {
    if(damage>=0){ // healing
        this->hp+=damage;
    }else{ // taking damage, returning 1 if dead
        if(this->hp+damage<=0){ // if dead
            return 1;
        }else{ // not dead
            this->hp+=damage;
        }
    }
    return 0;
}
CPlayer::CPlayer()=default;
CPlayer::~CPlayer() {
    for (int i =0; i<board.deck.size(); i++){
        delete board.deck[i];
    }
}