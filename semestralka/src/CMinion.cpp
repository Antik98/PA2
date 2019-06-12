//
// Created by David Pham on 5/23/2019.
//

#include "CMinion.h"
#include "CPlayer.h"
using namespace std;
class invalidHP{};
CMinion::CMinion(int id, bool isSpell, string &name, string &description, int manaRequired, int dmg, int hp) :
    CCard(id, isSpell,name,description,manaRequired),
    dmg(dmg),
    hp(hp) {
}

void CMinion::render() const {
    char escChar='\033';
    string suffix="[0m";
    string prefix="";
    prefix="[1;34m";// blue for minions
    cout << escChar << prefix << "(" << manaRequired << ") " << name << " HP: " << hp << " DMG: " << dmg <<escChar << suffix<< endl;
}

CMinion::CMinion(CMinion const & orig) : CCard(orig), dmg(orig.dmg), hp(orig.hp) {

}

CMinion *CMinion::clone() const {
    return new CMinion(*this);
}

int CMinion::takeDmg(int damage) {
    if(damage>=0){ // healing
        this->hp+=damage;
    }else{ // taking damage, returning 1 if dead
        if(this->hp+damage<=0){ // if dead
            return 1;
        }else{ // not dead
            this->hp+=damage;
        }
    }
    return 0;
}

int CMinion::apply() {
    return dmg*(-1);
}

int CMinion::getHP() {
    return hp;
}

int CMinion::setHP(int newHP) {
    if(newHP<=0) throw invalidHP();
    hp=newHP;
    return 0;
}

