//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CMINION_H
#define SEMESTRALKA_CMINION_H


#include "CCard.h"
using namespace std;

class CMinion : public CCard {
public:
    CMinion(bool isSpell, string &name, string &description, int manaRequired, int dmg, int hp);

    int dmg; // deals damage
    int hp; // health
    int attack(CMinion&); // TODO: Add player as receiver
    int takeDmg(int); // this can mean heal if number positive
};


#endif //SEMESTRALKA_CMINION_H
