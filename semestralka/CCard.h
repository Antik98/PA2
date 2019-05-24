//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARD_H
#define SEMESTRALKA_CCARD_H

#include <iostream>
#include <string>


using namespace std;

class CCard {
public:
    int id;
    bool isSpell;
    string name;
    string description;
    int manaRequired;

    CCard(int id, bool isSpell, string &name, string &description, int manaRequired);
};


#endif //SEMESTRALKA_CCARD_H
