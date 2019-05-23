//
// Created by David on 17.05.2019.
//

#include <iostream>

#include "CMainMenu.h"
using namespace std;

void CMainMenu::render() const {
    cout << "[1] New Game" << endl;
    cout << "[2] Load Game" << endl;
    cout << "[3] Exit" << endl;
}

int CMainMenu::parseInput() {
    cout << "Please enter selected option: " << flush;
    while (true){
        int selection = 0;
        cin >> selection;
        switch(selection){
            case 1:{
                cout << "Starting new game..." << endl;
                return 1;
            }
            case 2:{
                cout << "Loading game.... " << endl;
                return 2;
            }
            case 3:{
                cout << "Exiting game.... " << endl;
                return 3;
            }
            default:{
                cin.clear();
                string discard;
                getline(cin, discard);
                cout << "incorrect option. Please retry: " << endl;
                continue;
            }
        }
    }
}
