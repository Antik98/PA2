//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CARDDATABASE_H
#define SEMESTRALKA_CARDDATABASE_H


#include <iostream>
#include <vector>
#include "CCard.h"

class CardDatabase {
public:
    CardDatabase();
    vector<CCard*> database;
    bool parseDatabase(string&); // string name of database file
};


#endif //SEMESTRALKA_CARDDATABASE_H
