#include <iostream>
#include "lodePole.h"

using namespace std;
char** lodePole::createPole(int x, int y) {
    char** pole=new char* [x];
    sirka = x;
    delka = y;
    for (int i =0;i<x;i++){
        pole[i]= new char[y];
    }
    for(int i = 0; i<x;i++){
        for (int l=0;l<y;l++){
            pole[i][l]='~';
        }
    }
    return pole;
}
void lodePole::printPole() const {
    for(int i = 0; i<delka;i++){
        for (int l=0;l<sirka;l++){
            std::cout << this->pole[i][l];
        }
        std::cout<< endl;
    }
}

