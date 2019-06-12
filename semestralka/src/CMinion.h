//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CMINION_H
#define SEMESTRALKA_CMINION_H
#include <iostream>
#include "CCard.h"

class CMinion : public CCard {

public:
    CMinion(int id, bool isSpell, std::string &name, std::string &description, int manaRequired, int dmg, int hp);

    CMinion(CMinion const &);

    int dmg; // deals damage
    int hp; // health
    void render() const override;
    int takeDmg(int); // this can mean heal if number positive
    CMinion *clone() const override;
    int apply() override;
    virtual int getHP();
    virtual int setHP(int);

};
#endif //SEMESTRALKA_CMINION_H
