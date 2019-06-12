//
// Created by David on 17.05.2019.
//

#include <fstream>
#include <sstream>
#include <climits>
#include <typeinfo>
#include "CGame.h"
using namespace std;
class unexpectedInput{};

CGame::CGame() : gameActive(true), isAIGame(false), activePlayerIndex(0), activeWindowIndex(0)  {
    windows.push_back(new CMainMenu());
    windows.push_back(new CPauseMenu());
    windows.push_back(new CBoard(*this));
}

CGame::~CGame() {
    for (int i =0; i<windows.size(); i++){
        delete windows[i];
    }
    for (int i = 0 ; i < players.size(); i++){
        delete players[i];
    }
}

int requestInput3(int from, int to){
    int x;
    cin >> x;
    while(cin.fail() || cin.eof() || x<from || x>to){
        if(cin.eof()){
            throw unexpectedInput();
        }
        cout << "Wrong Input sir, please retry" << endl;
        cin.clear();
        string discard;
        getline(cin, discard);
        cin >> x;
    }
    return x;
}

bool saveFileExists(){
    ifstream f("saveFolder/saveFile");
    return f.good();
}

bool CGame::save() { // method that saves the current state of the game
    ofstream outFile;
    outFile.open("saveFolder/saveFile", ios:: out | ios::app);
    if (!outFile.good()){
        return false;
    }
    outFile << isAIGame << "\n";
    outFile << activePlayerIndex << "\n";
    for(int playerIndex=0 ; playerIndex<=1; playerIndex++){
        outFile << players[playerIndex]->hp << " " << players[playerIndex]->availableMana << "\n";
        for(int i =0; i<players[playerIndex]->hand.deck.size() ; i++){
            outFile << players[playerIndex]->hand.deck[i]->id;
            if((i+1)<players[playerIndex]->hand.deck.size()){
                outFile<<" ";
            }
        }
        outFile << "\n";// finished hand cards

        for(int i =0; i<players[playerIndex]->deck.deck.size() ; i++){
            outFile << players[playerIndex]->deck.deck[i]->id;
            if((i+1)<players[playerIndex]->deck.deck.size()){
                outFile<<" ";
            }
        }
        outFile <<"\n"; // finished deck cards

        for(int i =0; i<players[playerIndex]->board.deck.size() ; i++){
            outFile << players[playerIndex]->board.deck[i]->id << ":" << players[playerIndex]->board.deck[i]->getHP();
            if((i+1)<players[playerIndex]->board.deck.size()){
                outFile<<" ";
            }
        }
        if(playerIndex==0){
            outFile<<"\n"; // finished boardCards
        }
    }
    outFile.close();
    if(!outFile.good())
        return false;

    return true;
}

bool CGame::load() {
    if (!saveFileExists()) {
        cout << "Save File does not exist." << endl;
        return false;
    }
    ifstream saveFile;
    saveFile.open("saveFolder/saveFile"); // opened file
    if (!saveFile.good()) return false;
    string outputLine;

    istringstream iss;
    if (!getline(saveFile, outputLine)) // line1 -- isAIGame
        return false;
    iss.str(outputLine);
    iss >> isAIGame;
    iss.clear();

    if (!getline(saveFile, outputLine)) // line2 -- activePlayerIndex
        return false;
    iss.str(outputLine);
    int tmpPlayerIndex = 0;
    iss >> tmpPlayerIndex;
    if (tmpPlayerIndex != 0 && tmpPlayerIndex != 1) return false;
    activePlayerIndex = tmpPlayerIndex;
    iss.clear();

    if (!getline(saveFile, outputLine)) // line3 -- hp/mana
        return false;
    iss.str(outputLine);
    int tmphp = 30;
    int tmpMana = 10;
    iss >> tmphp >> tmpMana;
    if (tmphp <= 0 || tmpMana <= 0) return false;
    players[0]->hp = tmphp;
    players[0]->availableMana = tmpMana;
    iss.clear();


    if (!getline(saveFile, outputLine)) // line4 -- hand Deck
        return false;
    if (!players[0]->hand.loadSave(database, outputLine) || players[0]->hand.deck.size() > maxHandAmount) return false;

    if (!getline(saveFile, outputLine)) // line5 -- Deck Deck
        return false;
    if (!players[0]->deck.loadSave(database, outputLine) || players[0]->deck.deck.size() > deckAmount) return false;

    if (!getline(saveFile, outputLine)) // line6-- board Deck
        return false;
    if (!players[0]->board.loadSaveBoard(database, outputLine))
        return false;

    //------------------------ P2
    if (!getline(saveFile, outputLine)) // line7-- hp/mana
        return false;
    iss.str(outputLine);
    int tmphp2 = 30;
    int tmpMana2 = 10;
    iss >> tmphp2 >> tmpMana2;
    if (tmphp2 <= 0 || tmpMana2 <= 0) return false;
    players[1]->hp = tmphp2;
    players[1]->availableMana = tmpMana2;
    iss.clear();

    if (!getline(saveFile, outputLine)) // line8 -- hand Deck
        return false;
    if (!players[1]->hand.loadSave(database, outputLine) || players[1]->hand.deck.size() > maxHandAmount) return false;

    if (!getline(saveFile, outputLine)) // line9 -- Deck Deck
        return false;
    if (!players[1]->deck.loadSave(database, outputLine) || players[1]->deck.deck.size() > deckAmount) return false;

    if (!getline(saveFile, outputLine) && saveFile.eof()) // line10 -- board Deck
        outputLine="";
    if (!players[1]->board.loadSaveBoard(database, outputLine))
        return false;

    return true;
}

int CGame::start() {
    system("clear");
    gameActive=true;
    activeWindowIndex=0;
    windows[activeWindowIndex]->render();
    int mainMenuSelection= windows[activeWindowIndex]->parseInput();
    switch (mainMenuSelection){
        case 1:{ // start new game -
            isAIGame=false;
            gameLoaded=false;
            cout << "Generating random decks...." << endl;
            players.push_back(new CHumanPlayer(false, database));
            players.push_back(new CHumanPlayer(false, database));
            break;
        }
        case 2:{ // start new game - PvAI
            isAIGame=true;
            gameLoaded=false;
            players.push_back(new CHumanPlayer(false, database));
            players.push_back(new CAIPlayer(false, database));
            break;
        }
        case 3:{ // load game
            gameLoaded=true;
            players.push_back(new CHumanPlayer(true, database));
            players.push_back(new CAIPlayer(true, database));
            if(!load()){
                cout << "Load Game Unsuccessful" << endl;
                return 0;
            }
            break;
        }
        case 4:// exit
            return 0;
        default:
            return 0;
    }
    activeWindowIndex=2;
    cout << "Game start." << endl;
    cout << endl << endl<< endl<< endl;
    gameActive=true;
    while(gameActive){
        system("clear");
        int enemyPlayerIndex;
        if(activePlayerIndex==0){
            enemyPlayerIndex=1;
        }else{
            enemyPlayerIndex=0;
        }

        if(!players[activePlayerIndex]->isAlive ){ // checks end of game
            gameActive=false;
            cout << "Player " << enemyPlayerIndex+1 << " Wins!!!!!!!!!!!!!" << endl;
            break;
        }else if(!players[enemyPlayerIndex]->isAlive ){
            gameActive=false;
            cout << "Player " << activePlayerIndex+1 << " Wins!!!!!!!!!!!!!" << endl;
            break;
        }


        if(typeid(*(players[activePlayerIndex]))== typeid(CHumanPlayer)) // renders out
            windows[activeWindowIndex]->render();

        int choice=windows[activeWindowIndex]->parseInput(); // polymorphism

        if(activeWindowIndex==2){ // parseInput returns from CBoard
            switch(choice){
                case 1:{// player died
                    continue;
                }
                case 2:{ // change players
                    players[activePlayerIndex]->availableMana=10;
                    if (!isAIGame) {
                        system("clear");
                        cin.ignore(INT_MAX, '\n');
                        cout << "Player [" << activePlayerIndex << "] has finished playing. Press ENTER to continue." << endl;
                        cin.get();
                    }

                    if(activePlayerIndex==0){
                        activePlayerIndex=1;
                    }else{
                        activePlayerIndex=0;
                    }
                    break;
                }
                case 3:{ // request change menu to pause
                    activeWindowIndex=1;
                    break;
                }
            }
        }else if(activeWindowIndex==1){ // parseInput return from PauseMenu
            switch(choice){
                case 1: { // resume, go back to board
                    activeWindowIndex=2;
                    break;
                }
                case 2: { // save
                    if(saveFileExists()){
                        cout<< "A save File exists. Do you wish to overwrite? " << endl;
                        cout<< "[1] Yes." << endl;
                        cout<< "[2] No." << endl;
                        int choice=requestInput3(1,2);
                        switch (choice){
                            case 1:{
                                if( remove( "saveFolder/saveFile" ) != 0 ){
                                    cout<< "Error deleting file." << endl;
                                    break;
                                }
                                else{
                                    cout << "File deleted successfully." << endl;
                                    if(save()){
                                        cout << "Save Successful" << endl;
                                    }else{
                                        cout << "Save Unsuccessful" << endl;
                                    }
                                }
                                break;
                            }
                            case 2:{
                                cout << "Save Canceled." << endl;
                                break;
                            }
                        }
                    }else{
                        if(save()){
                            cout << "Save Successful" << endl;
                        }else{
                            cout << "Save Unsuccessful" << endl;
                        }
                    }
                    break;
                }
                case 3: { // quit game
                    return 0;
                }
            }
        }
    }
return 0;
}
