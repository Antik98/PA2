//
// Created by David Pham on 5/23/2019.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "CardDatabase.h"
#include "CSpell.h"
#include "CMinion.h"

class cardDatabaseException{};

CardDatabase::CardDatabase() {
    string dirCardDatabase="cards/cards.txt";
    if(!parseDatabase(dirCardDatabase))
        throw cardDatabaseException();
}

bool CardDatabase::parseDatabase(string & fileName) {
    int id;
    bool isSpell;
    char dummy1;
    char dummy2;
    string name;
    string description;
    int manaRequired;
    int dmg;
    int hp;
    ifstream inputFile;
    inputFile.open(fileName);
    if(!inputFile.good()) return false;
    string inputLine;
    bool firstLine=true;
    string tmp;
    while(getline(inputFile, inputLine)){ // line 1
        name="";
        description="";
        if(!firstLine) {
            getline(inputFile, inputLine);
        }
        firstLine=false;
        istringstream iss;
        iss.str(inputLine);
        iss >> id >> dummy1;
        if(dummy1!='{') return false; // returns false if not reached {

        getline(inputFile, inputLine);// line 2 -- isSpell
        iss.str(inputLine);
        iss.seekg(1);
        iss >> isSpell;

        getline(inputFile, inputLine);// line 3 -- name
        iss.str(inputLine);
        iss.seekg(1);
        while(!iss.eof()){
            iss >> tmp;
            name+=tmp;
            if(!iss.eof())
                name+=" ";
        }

        getline(inputFile, inputLine);// line 4 -- description
        iss.str(inputLine);
        iss.seekg(1);
        while(!iss.eof()){
            iss >> tmp;
            description+=tmp;
            if(!iss.eof())
                description+=" ";
        }

        getline(inputFile, inputLine);// line 5 -- manaRequired
        iss.str(inputLine);
        iss.seekg(1);
        iss >> manaRequired;

        if(isSpell){ // spell card
            getline(inputFile, inputLine);// line 6 -- dmg, negative if damaging, positive if healing
            iss.str(inputLine);
            iss.seekg(1);
            iss >> dmg;

            //check if spell valid
            if(isSpell!=1 || name.empty() || description.empty() || manaRequired<0) return false;

            database.push_back(new CSpell(isSpell, name, description, manaRequired, dmg));
        }else { // minion card
            getline(inputFile, inputLine);// line 6 -- dmg
            iss.str(inputLine);
            iss.seekg(1);
            iss >> dmg;

            getline(inputFile, inputLine);// line 7 -- hp
            iss.str(inputLine);
            iss.seekg(1);
            iss >> hp;

            //check if minion valid before insert
            if(isSpell!=0 || name.empty() || description.empty() || manaRequired<0 || dmg<0 || hp<0) return false;

            database.push_back(new CMinion(isSpell, name, description, manaRequired, dmg, hp));
        }

        getline(inputFile, tmp);// line 7/8 -- ending bracket - could fail this leads to incorrect number of rows, throw exception
        if(tmp.size()==1 && tmp[0]!='}') return false; // returns false if not reached }

    }
    return true;
}
