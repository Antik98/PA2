#pragma once

#include <string>

using namespace std;

class Card {
public:
	Card(const string &name = "unknown", int mana = 0, int attack = 0) : name(name), mana(mana), attack(attack) {}
	void Print() const;
	friend ostream &operator <<(ostream &os,const Card &b );


private:
	string name;
	int mana;
	int attack;
};