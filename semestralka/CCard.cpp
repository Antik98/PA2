//
// Created by David Pham on 5/22/2019.
//

#include "CCard.h"

CCard::CCard(bool isSpell, string &name, string &description, int manaRequired)
    : isSpell(isSpell),
    name(name),
    description(description),
    manaRequired(manaRequired) {}
