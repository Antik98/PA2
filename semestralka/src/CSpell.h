//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CSPELL_H
#define SEMESTRALKA_CSPELL_H
#include <iostream>
#include "CCard.h"
#include "CMinion.h"


class CSpell : public CCard{
public:
    int dmg; // negative if deals damage, positive heals

    CSpell(int id, bool isSpell, std::string name, std::string description, int mana, int dmg);
    CSpell(CSpell const &);
    void render() const;
    virtual int apply();
    virtual CSpell* clone() const;
    virtual int takeDmg(int);
    virtual int getHP();
    virtual int setHP(int);
};


#endif //SEMESTRALKA_CSPELL_H
