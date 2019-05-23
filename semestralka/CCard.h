//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARD_H
#define SEMESTRALKA_CCARD_H

#include <string>
#include "CMinion.h"

using namespace std;

class CCard {
public:
    bool isSpell;
    string name;
    string description;
    int manaRequired;

    CCard(bool isSpell, string &name, string &description, int manaRequired);
    virtual int attack(CMinion&)=0;
};


#endif //SEMESTRALKA_CCARD_H
