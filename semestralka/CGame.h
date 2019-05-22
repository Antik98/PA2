//
// Created by David on 17.05.2019.
//

#ifndef SEMESTRALKA_CGAME_H
#define SEMESTRALKA_CGAME_H

#include <vector>
#include "CWindow.h"

using namespace std;
class CGame {
public:
    CGame();
    ~CGame();
protected:
    vector<CWindow*> windows;
};


#endif //SEMESTRALKA_CGAME_H
