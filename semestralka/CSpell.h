//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CSPELL_H
#define SEMESTRALKA_CSPELL_H
#include <iostream>
#include "CCard.h"

using namespace std;

class CSpell : public CCard{
public:
    int dmg; // negative if deals damage, positive heals

    CSpell(int id, bool isSpell, string name, string description, int mana, int dmg);
    //int apply(CMinion&);
};


#endif //SEMESTRALKA_CSPELL_H
