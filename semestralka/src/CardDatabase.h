//
// Created by David Pham on 5/23/2019.
//

#ifndef SEMESTRALKA_CARDDATABASE_H
#define SEMESTRALKA_CARDDATABASE_H


#include <iostream>
#include <vector>
#include "CCard.h"
static const int databaseAmount=33;

class CardDatabase {
public:
    ~CardDatabase(){
        for(int i=0; i <database.size(); i++){
            delete database[i];
        }
    }
    CardDatabase();
    std::vector<CCard*> database;
    bool parseDatabase(std::string&); // string name of database file
    void render() const;
};


#endif //SEMESTRALKA_CARDDATABASE_H
