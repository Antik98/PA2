//
// Created by David Pham on 5/22/2019.
//

#ifndef SEMESTRALKA_CCARDSTACK_H
#define SEMESTRALKA_CCARDSTACK_H

#include <iostream>
#include <vector>
#include "CCard.h"
#include "CardDatabase.h"

using namespace std;
//id in database also correspond to index in vector


class CCardStack {
public:
    vector<CCard*> parseDeckFile(CardDatabase&, string);
protected:
    vector<CCard*> deck;
};


#endif //SEMESTRALKA_CCARDSTACK_H
