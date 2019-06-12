//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARD_H
#define SEMESTRALKA_CCARD_H

#include <iostream>
#include <string>

/**
 * Abstract Superclass CCard
 * Applied Polymorphism
 * Can be Minion or Spell
 */
class CCard {
public:
    int id;
    bool isSpell;
    std::string name;
    std::string description;
    int manaRequired;
    /**
     * Visual function, for CHumanPlayer, renders out contents of both boards
     */
    virtual void render() const = 0;
    /**
     * Constructor
     * @param id - based on database
     * @param isSpell - boolean isSpell
     * @param name  - string name
     * @param description - string description
     * @param manaRequired - int required mana to cast
     */
    CCard(int id, bool isSpell, std::string& name, std::string& description, int manaRequired);
    /**
     * Implicit copy constructor
     */
    CCard(CCard const &);
    /**
     * Destructor
     */
    virtual ~CCard();
    /**
     * Clones CMinion or CSpell
     * @return allocated CMinion or CSpell
     */
    virtual CCard* clone() const=0;
    /**
     * @return Damage of card - negative, Heal of card - positive
     */
    virtual int apply()=0;
    virtual int takeDmg(int)=0;
    virtual int getHP() const = 0;
    virtual int setHP(int)=0;
};


#endif //SEMESTRALKA_CCARD_H
