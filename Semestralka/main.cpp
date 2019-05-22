#include <iostream>
#include <ncurses.h>
//#include "CBoard.h"
//#include "CCard.h"
#include "CGame.h"
//#include "CMenu.h"
//#include "CMainMenu.h"
//#include "CPauseMenu.h"
//#include "CMinion.h"
//#include "CWindow.h"
//#include "CSpell.h"



using namespace std;

int main() {
    CGame game;
    game.init();
    while(1){
        game.play();
    }
}