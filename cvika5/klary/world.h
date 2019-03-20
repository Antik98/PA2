//
// Created by phamducm on 3/20/19.
//

#ifndef KLARY_WORLD_H
#define KLARY_WORLD_H

#include <iostream>
using namespace std;

class CBlok{
public:
    int x;
    int y;
    int width;
    int height;
    CBlok(int x, int y, int width, int height);
};

class CWorld {
public:
    CWorld(string,int);
    ~CWorld();
    string nazev;
    int currentfree;
    int pocetsvetu;
    CBlok** pole;
    friend ostream &operator<<(ostream &os, const CWorld &world);
    CWorld operator+=(const int*) const;
};

#endif //KLARY_WORLD_H
