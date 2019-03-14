#include <string>
#include <iostream>
#include <algorithm>
#include "deck.hpp"

using namespace std;
const int MAXIMUM_DECK_SIZE = 20;

Deck::Deck(string name) : name(name) {
    cards_size = MAXIMUM_DECK_SIZE;
    cards_count = 0;
    cards = new Card[cards_size];
}

Deck::~Deck() {
   Deck tmp(f delete[] cards;
}

Deck::Deck(const Deck &other_deck) {
    name = other_deck.name;
    cards_count = other_deck.cards_count;
    cards_size = other_deck.cards_size;
    cards = new Card[cards_size];
    for (int i = 0; i < cards_count; ++i) {
        cards[i] = other_deck.cards[i];
    }
}

void Deck::Print() const {
    cout << "Deck " << name << " has " << cards_count << " cards." << endl;
    for (int i = 0; i < cards_count; ++i) {
        cards[i].Print();
    }
}
ostream& operator<<(ostream& os, const Deck &b){
    b.Print();
    return os;
}
Deck operator+(const Deck &firstDeck, const Deck &secondDeck){
    Deck tmp(firstDeck.name + secondDeck.name);

    int sizeFirst=firstDeck.cards_count;
    int  sizeSecond=secondDeck.cards_count;
    for(int i=0;i<sizeFirst;i++){
        tmp.cards[i]=firstDeck.cards[i];
    }
    for(int i=sizeFirst;i<sizeFirst+sizeSecond;i++){
        int l=i-sizeFirst;
        tmp.cards[i]=secondDeck.cards[l];
    }
    return tmp;
}