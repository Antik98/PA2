//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CMINION_H
#define SEMESTRALKA_CMINION_H
#include <iostream>
#include "CCard.h"


/**
 * CMinion - Child class of super class CCard
 * render() - Shows basic information about the card *not used if AIplayer
 * takeDmg() - takes amount of delt damage/healing applies to itself, returns 1 if Minion dies after taken effect
 * apply() - getter - Minion returns its dmg in negative, in preparation for dealing damage
 * getHP() - getter - returns minion's hp
 * setHP() - setter - sets minion's hp, checks if negative
 */
class CMinion : public CCard {

public:
    CMinion(int id, bool isSpell, std::string &name, std::string &description, int manaRequired, int dmg, int hp);

    CMinion(CMinion const &);

    int dmg; // deals damage
    int hp; // health
    void render() const override;
    /**
     * Applies damage/heal to itself
     * @return 0 if survives blow, 1 if dies from blow
     */
    int takeDmg(int) override; // this can mean heal if number positive
    CMinion *clone() const override;
    int apply() override;
    /**
     * Getter
     * @return HP of CMinion
     */
    int getHP() const override;
    /**
     * Setter
     * @return 0 if successful
     */
    int setHP(int) override;

};
#endif //SEMESTRALKA_CMINION_H
