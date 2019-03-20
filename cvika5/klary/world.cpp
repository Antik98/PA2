//
// Created by phamducm on 3/20/19.
//

#include "world.h"

CWorld::CWorld(string name,int n = 1000) {
    nazev=name;
    pocetsvetu=n;
    currentfree=n;
    pole=new CBlok*[n];
}
CWorld::~CWorld() {
    delete[] pole;
}

ostream &operator<<(ostream &os, const CWorld &world) {
    os << "nazev: " << world.nazev << " pocetsvetu: " << world.pocetsvetu;
    return os;
}

CWorld CWorld::operator+=(const int * blok) const {
    pole[pocetsvetu-currentfree]=new CBlok(blok[0], blok[1], blok[2], blok[3]);
}

CBlok::CBlok(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {

}
