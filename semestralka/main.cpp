#include <iostream>
#include "CGame.h"
using namespace std;
int main() {
    CGame game;
    if(game.start()==0){
        return 0;
    }else{
        cout << "Game ended with an error" << endl;
    }
}