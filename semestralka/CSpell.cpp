//
// Created by David Pham on 5/23/2019.
//

#include "CSpell.h"


CSpell::CSpell(bool isSpell, string name, string description, int mana, int dmg) : CCard(isSpell,name,description,mana), dmg(dmg)
{

}

int CSpell::apply(CMinion &) {
    return 0;
}
