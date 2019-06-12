//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARD_H
#define SEMESTRALKA_CCARD_H

#include <iostream>
#include <string>


class CCard {
public:
    int id;
    bool isSpell;
    std::string name;
    std::string description;
    int manaRequired;
    virtual void render() const = 0;
    CCard(int id, bool isSpell, std::string& name, std::string& description, int manaRequired);
    CCard(CCard const &);
    virtual ~CCard();
    virtual CCard* clone() const=0;
    virtual int apply()=0;
    virtual int takeDmg(int)=0;
    virtual int getHP()=0;
    virtual int setHP(int)=0;
};


#endif //SEMESTRALKA_CCARD_H
