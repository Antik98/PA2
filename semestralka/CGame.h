//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CGAME_H
#define SEMESTRALKA_CGAME_H

#include <vector>
#include "CWindow.h"
#include "CardDatabase.h"

using namespace std;
class CGame {
public:
    CGame();
    ~CGame();
    int start();
protected:
    int activeWindowIndex;
    vector<CWindow*> windows;
    CardDatabase database;


};


#endif //SEMESTRALKA_CGAME_H
