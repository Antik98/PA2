//
// Created by Duc Minh Pham on 2019-05-06.
//
#include <iostream>
#include <unistd.h>
#include "CWindow.h"
#include "CGame.h"
#include "CBoard.h"

using namespace std;
CGame::CGame() {

}

CGame::~CGame() {

}

bool CGame::init() { // initializing the game, load in files
    system("clear");
    cout << "Initializing game" << endl;
    usleep(1000000);
    system("clear");
    return false;
}
bool CGame::play() {
    CBoard mainBoard;
    mainBoard.render();
}
bool CGame::save() { // save game progress
    return false;
}

bool CGame::load() { // load game progress
    return false;
}