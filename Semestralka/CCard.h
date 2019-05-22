//
// Created by Duc Minh Pham on 2019-05-06.
//

#ifndef SEMESTRALKA_CCARD_H
#define SEMESTRALKA_CCARD_H

#include <iostream>
#include <string>
using namespace std;
class CCard {
    int id;
    string name;
    string desc;
    vector<CAbility> Abilities;
public:
    CCard();
    virtual ~CCard();
    void print();
};


#endif //SEMESTRALKA_CCARD_H
