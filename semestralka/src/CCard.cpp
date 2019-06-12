//
// Created by David Pham on 5/22/2019.
//

#include "CCard.h"
#include "CPlayer.h"
using namespace std;
CCard::CCard(int id, bool isSpell, string &name, string &description, int manaRequired)
    : id(id),
    isSpell(isSpell),
    name(name),
    description(description),
    manaRequired(manaRequired) {}

CCard::CCard(CCard const &orig) : id(orig.id),
                                  isSpell(orig.isSpell),
                                  name(orig.name),
                                  description(orig.description),
                                  manaRequired(orig.manaRequired) {

}

CCard::~CCard() {

}


