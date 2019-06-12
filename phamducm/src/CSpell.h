//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CSPELL_H
#define SEMESTRALKA_CSPELL_H
#include <iostream>
#include "CCard.h"
#include "CMinion.h"

/**
 * Child class of super class CCard
 * render() - graphic render of card, shows Name, values and description of spell
 */
class CSpell : public CCard{
public:
    int dmg; // negative if deals damage, positive heals

    CSpell(int id, bool isSpell, std::string name, std::string description, int mana, int dmg);
    CSpell(CSpell const &);
    void render() const;
    /**
     * Getter
     * @return Damage/Heal dealt by card
     */
    virtual int apply();
    /**
     * Allocates seperate entity
     * @return - returns newly allocated copy
     */
    virtual CSpell* clone() const;
    /**
     * Not Used
     */
    virtual int takeDmg(int);
    /**
     * Not Used
     */
    virtual int getHP() const;
    /**
     * Not Used
     */
    virtual int setHP(int);
};


#endif //SEMESTRALKA_CSPELL_H
