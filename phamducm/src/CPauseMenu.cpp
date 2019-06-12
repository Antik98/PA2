//
// Created by David on 17.05.2019.
//
#include <iostream>
#include "CPauseMenu.h"
using namespace std;

CPauseMenu::CPauseMenu() {

}

int requestInput2(int from, int to){
    int x;
    cin >> x;
    while(cin.fail() || cin.eof() || x<from || x>to){
        cout << "Wrong Input sir, please retry" << endl;
        cin.clear();
        string discard;
        getline(cin, discard);
        cin >> x;
    }
    return x;
}

void CPauseMenu::render() const {
    cout << "Pausing game ...." << endl;
    cout << "[1] Resume" << endl;
    cout << "[2] Save" << endl;
    cout << "[3] Quit Game" << endl;
}

int CPauseMenu::parseInput() {
    cout << "Please enter selected option: " << flush;
    int selection=requestInput2(1,3);

    switch(selection) {
        case 1: {
            cout << "Resuming Game.... " << endl;
            return 1;
        }
        case 2: {
            cout << "Saving game.... " << endl;
            return 2;
        }
        case 3: {
            cout << "Quitting game.... " << endl;
            return 3;
        }
    }
    return 0;
}
