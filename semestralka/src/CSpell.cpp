//
// Created by David Pham on 5/23/2019.
//

#include "CSpell.h"
class spellUsedIncorrectly {};
class dynamicCastFailed {};

using namespace std;

CSpell::CSpell(int id, bool isSpell, string name, string description, int mana, int dmg) : CCard(id,isSpell,name,description,mana), dmg(dmg)
{

}

CSpell::CSpell(CSpell const & orig) : CCard(orig), dmg(orig.dmg) {

}

CSpell *CSpell::clone() const {
    return new CSpell(*this);
}


void CSpell::render() const {
    char escChar='\033';
    string suffix="[0m";
    string prefix="";
    prefix="[1;33m";// yellow for spells
    if(dmg>=0)
        cout << escChar<< prefix << "(" << manaRequired << ") " << name << " Heals: +" << dmg << escChar << suffix<< endl;
    else
        cout << escChar<< prefix << "(" << manaRequired << ") " << name << " DMG: " << dmg*(-1) << escChar << suffix<< endl;
}

int CSpell::apply() {
    return dmg;
}

int CSpell::takeDmg(int) {
    throw spellUsedIncorrectly();
}

int CSpell::getHP() {
    throw spellUsedIncorrectly();
}

int CSpell::setHP(int) {
    throw spellUsedIncorrectly();
}

