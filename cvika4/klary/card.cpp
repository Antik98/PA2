#include "card.hpp"
#include <iostream>

void Card::Print()const {
	cout << "Card name: " << name << " mana: " << mana << " attack: " << attack << endl;
}
ostream& operator<<(ostream& os, const Card &b){
	b.Print();
	return os;
}
