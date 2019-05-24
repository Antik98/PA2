//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CGAME_H
#define SEMESTRALKA_CGAME_H

#include <vector>
#include "CWindow.h"
#include "CardDatabase.h"
#include "CPlayer.h"

using namespace std;
class CGame {
public:
    CGame();
    ~CGame();
    int start();
protected:
    int activeWindowIndex;
    vector<CWindow*> windows;
    static CardDatabase database;
    vector<CPlayer*> players;
};


#endif //SEMESTRALKA_CGAME_H
