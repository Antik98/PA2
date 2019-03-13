#include <iostream>
#include <fstream>

#include "card.hpp"
#include "deck.hpp"

using namespace std;
int main() {

    Deck cool_deck("Cool_deck");
    Card card_knight("Knight", 6, 10),
         card_dragon("Dragon", 10, 100),
         card_skeleton("Skeleton", 1, 1),
         card_dwarf("Dwarf", 3, 4);

    // a) += operator overload

    cool_deck += card_knight;
    cool_deck += card_dragon;
    cool_deck += card_skeleton;
    cool_deck += card_dwarf;
     // b) print deck
    cout << endl << "====================== B ======================" << endl;
    cout << cool_deck << endl;
    // c) operator []
    cout << endl << "====================== C ======================" << endl;
    Card card = cool_deck[2];
    cout << card << endl;


    Deck deamon_deck("Deamon_deck");
    Card card_deamon("Deamon", 8, 20);
    deamon_deck += card_deamon;

    // d) merge two decks
    cout << endl << "====================== D ======================" << endl;
    Deck ultimate_deck = cool_deck + deamon_deck;
    cout << ultimate_deck << endl;

  /*  // e) general exception
    cout << endl << "====================== E ======================" << endl;
    // wrap this command, catch and print the exception
        ultimate_deck = ultimate_deck + ultimate_deck + ultimate_deck + ultimate_deck +
                        ultimate_deck;

    // f) out_of_range exception
    cout << endl << "====================== F ======================" << endl;
    // wrap these two commands, catch and print the exception
        card = ultimate_deck[10];
        cout << card << endl;

    // g) sort
    cout << endl << "====================== G ======================" << endl;
    ultimate_deck.sort();
    cout << ultimate_deck << endl;

    // h) remove cards
    cout << endl << "====================== H ======================" << endl;
    Deck begin_deck = ultimate_deck | 6;
    cout << begin_deck << endl;

    //     i) operator [] again
    cout << endl << "====================== I ======================" << endl;
    begin_deck[0] = card_skeleton;
    cout << begin_deck << endl;
    const Deck const_deck = ultimate_deck;
    cout << const_deck[4]<<endl;

    cout<<((ultimate_deck|5)+cool_deck)[6]<<endl;*/
    return 0;
}