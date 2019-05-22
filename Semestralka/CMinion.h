//
// Created by Duc Minh Pham on 2019-05-06.
//

#ifndef SEMESTRALKA_CMINION_H
#define SEMESTRALKA_CMINION_H

#include "CCard.h"
class CMinion : public CCard {
    int dmg;
    int health;
public:
    void GetHit();
    void Attack();
};


#endif //SEMESTRALKA_CMINION_H
