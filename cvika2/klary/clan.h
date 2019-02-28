//
// Created by phamducm on 2/27/19.
//

#ifndef KLARY_CLAN_H
#define KLARY_CLAN_H
#include <iostream>
#include "Member.h"

using namespace std;

class clan {
public:
    string jmeno;
    Member clenove[20];
    int pocetclenu=0;
    int get_silaklanu();
    void printKlan();
    void pridat_clena();
};
int clan::get_silaklanu() {
    int suma=0;
    for (int i =0; i<4;i++){
        suma+=clenove[i].power;
    }
    return suma;
};
void clan::printKlan() {
    cout << "Jmeno klanu : " << clan::jmeno << endl << "Pocet clenu: "<< clan::pocetclenu << endl << "Sila klanu: " << get_silaklanu() << endl << endl;
    cout << "Clenove klanu " << clan::jmeno << ": " << endl;
    for(int i = 0;i<pocetclenu;i++){
        cout<< "Jmeno: " << clan::clenove[i].name << endl;
        cout<< "Sila: " << clan::clenove[i].power << endl;
    }
};
void clan::pridat_clena() {
    Member clen;
    for(int i = 0; i<=10;i++){
        clen.name += 'a' + rand() % ('z'-'a');
    }
    clen.power=rand() % 10000;
    clan::clenove[pocetclenu].name=clen.name;
    clan::clenove[pocetclenu].power=clen.power;
    clan::pocetclenu++;
};
#endif //KLARY_CLAN_H
