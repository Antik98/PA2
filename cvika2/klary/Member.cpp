//
// Created by phamducm on 2/27/19.
//
#include <iostream>
#include "Member.h"
#include "clan.h"
using namespace std;

int main() {
    srand(time(NULL));

//    Member klara ;
//    klara.name = "Klara";
//    klara.power = 9000;
//    klara.zbran = ma;
//    klara.print();
//
//    Member tomas ;
//    tomas.name = "Tomas";
//    tomas.power = 9000;
//    tomas.zbran = ma;
//    tomas.print();
//
//    Member patrik ;
//    patrik.name = "Patrik";
//    patrik.power = 9000;
//    patrik.zbran = ma;
//    patrik.print();
//
    Member ondra ;
    ondra.name = "Ondra";
    ondra.power = 9000;
    ondra.zbran = ma;
    ondra.print();

    cout << endl << endl;

    clan FIT;
    FIT.jmeno = "FIT";
    FIT.pridat_clena();
    FIT.pridat_clena();
    FIT.pridat_clena();
    FIT.printKlan();
    return 0;
}