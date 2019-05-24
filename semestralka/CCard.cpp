//
// Created by David Pham on 5/22/2019.
//

#include "CCard.h"

CCard::CCard(int id, bool isSpell, string &name, string &description, int manaRequired)
    : id(id),
    isSpell(isSpell),
    name(name),
    description(description),
    manaRequired(manaRequired) {}
