//
// Created by David Pham on 5/23/2019.
//

#include "CMinion.h"

CMinion::CMinion(int id, bool isSpell, string &name, string &description, int manaRequired, int dmg, int hp) :
    CCard(id, isSpell,name,description,manaRequired),
    dmg(dmg),
    hp(hp) {
}
