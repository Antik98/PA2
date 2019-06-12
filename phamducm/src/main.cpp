#include <iostream>
#include "CGame.h"
using namespace std;
class unexpectedInput{};
class cardDatabaseException{};
int main() {
    try{
        cout << "Zapnuti hry" << endl;
        CGame game;
        if(game.start()==0){
            return 0;
        }else{
            cout << "Game ended with an error" << endl;
        }
    }catch(unexpectedInput){
        cout << "Unexpected Input detected" << endl;
    }catch(cardDatabaseException){
        cout << "Error in CardDatabase Initialization" << endl;
    }
}