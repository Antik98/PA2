//
// Created by David on 17.05.2019.
//

#include <iostream>

#include "CMainMenu.h"
using namespace std;
class unexpectedInput{};

void CMainMenu::render() const {
    cout << "[1] New Game - PvP" << endl;
    cout << "[2] New Game - PvAI" << endl;
    cout << "[3] Load Game" << endl;
    cout << "[4] Exit" << endl;
}

int CMainMenu::parseInput() {
    cout << "Please enter selected option: " << flush;
    while (true){
        int selection = 0;
        cin >> selection;
        switch(selection){
            case 1:{
                cout << "Starting new game PvP..." << endl;
                return 1;
            }
            case 2:{
                cout << "Starting new game PvAI.... " << endl;
                return 2;
            }
            case 3:{
                cout << "Loading game.... " << endl;
                return 3;
            }
            case 4:{
                cout << "Exiting game.... " << endl;
                return 4;
            }
            default:{
                if(cin.eof()){
                    throw unexpectedInput();
                }
                cin.clear();
                string discard;
                getline(cin, discard);
                cout << "incorrect option. Please retry: " << endl;
                continue;
            }
        }
    }
}
