//
// Created by phamducm on 3/29/19.
//

#ifndef CHLUDIL_POVOLANI_H
#define CHLUDIL_POVOLANI_H

#include <iostream>
#include <string>
using namespace std;

class Povolani {
public:
    virtual int Mystika();
    virtual int BojNaBlizko();
    virtual int BojNaDalku_strelba();
    virtual int BojNaDalku_vrh();
    virtual int Smlouvani();

protected:
    int m_uroven;
    string m_jmeno;
};
class Bojovnik : public Povolani{
public:
    Bojovnik(int uroven = 0)
        :Povolani::m_uroven(uroven) {
        cout<< "Vytvoril se Bojovnik" << endl;
    }
    int Bojovnik::Mystika() {
        cout << "Pouzil se Bojovnik:: mystika()" << endl;
    }

protected:
};


#endif //CHLUDIL_POVOLANI_H
