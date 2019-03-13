#pragma once
#include "card.hpp"
using namespace std;
class Deck {
public:
	Deck(string name);
	~Deck();
	Deck(const Deck& other_deck); //Copy constructor, don't remove unless you know what you are doing
	void Print() const;
	Deck& operator+=(const Card &b){
		cards[cards_count]=b;
        cards_count++;
		return *this;
	};
	friend ostream& operator<<(ostream& os, const Deck &b);
	Card operator[](int l){
		Card tmp;
		tmp = cards[l];
		return tmp;
	}
	friend Deck operator+(const Deck &firstDeck, const Deck &secondDeck);
private:
	string name;
	Card * cards;
	int cards_count;
	int cards_size;
};