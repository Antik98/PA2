//
// Created by phamducm on 2/27/19.
//

#ifndef KLARY_MEMBER_H
#define KLARY_MEMBER_H

#include <iostream>
using namespace std;
enum zbran_ {ma,nema};
class Member {
public:
    string name;
    int power;
    zbran_ zbran;
    void print();
};
void Member::print() {
        cout << "Jmeno: " << name << endl << "Sila: " << power << endl << "Je ozbrojen: " << zbran << endl;
}


#endif //KLARY_MEMBER_H
