#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Fighter{
public:
    enum class color{BLUE = 0x0000ff , YELLOW = 0xffff00};
    Fighter(string& name, color, int);
    virtual void getHit(int)=0;
    virtual void attack ( Fighter & victim)=0;
    virtual bool isAlive()const{
        return (hp>0);
    }
protected:
    int hp;
    string name;
    color type;
};

Fighter::Fighter(string& name, Fighter::color profese, int hp)
    :hp(hp), name(name), type(profese){
    cout<< "Fighter created ok" << endl;
}

class Knight : public Fighter{
public:
    Knight(string name, color type, int hp, int sword, int fists, int shield, int shieldDur);
    void attack (Fighter & victim);
    void getHit(int);
    ostream& operator << (ostream&) const;
private:
    int swordDmg;
    int fistDmg;
    int shield;
    int shieldDur;
};

Knight::Knight(string  name, color type, int hp, int sword, int fists, int shield, int shieldDur)
    : Fighter(name, type, hp), shield(shield), swordDmg(sword), fistDmg(fists), shieldDur(shieldDur) {};


void Knight::getHit(int dmg){
    if(!shieldDur){
        hp-=dmg;
    }
    if(dmg>shield)
        hp-=(dmg-shield);
    shieldDur--;
}

void Knight::attack(Fighter &victim) {
    victim.getHit(swordDmg+fistDmg);
}

ostream& Knight::operator<<(ostream &os) const {
    os<< "[k]" << name << "(" <<hp << ")";
    return os;
}


int main() {
    Knight x0("PrvniRytir", Fighter::color::BLUE , 1000, 20, 5, 100, 100 );
    Knight x1("DruhyRytir", Fighter::color::BLUE , 2000, 20, 5, 100, 100 );
    x0.attack(x1);
}