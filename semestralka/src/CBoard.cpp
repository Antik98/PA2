//
// Created by David on 17.05.2019.
//

#include <limits>
#include <ctime>
#include "CBoard.h"
#include "CGame.h"


using namespace std;
class unexpectedInput{};
int requestInput(int from, int to){
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
int chooseTarget(CGame* gamePtr, int playerIndex){

    int index =0;
    cout << "[" << index++ << "]" << " The Player" << endl;

    for(int i = 0;  i<gamePtr->players[playerIndex]->board.deck.size();i++){
        cout << "[" << index++ << "]";
        gamePtr->players[playerIndex]->board.deck[i]->render();
    }
    while(true){
        int choice=requestInput(0, index);
        if(choice >=0 && choice<=index){
            return choice;
        }else{
            cout << "Wrong target!" << endl;
        }
    }

}

int attack(CGame* gamePtr, int damage){
    cout << "[0] Your enemy Board, [1] Your Board" << endl;
    int targetBoard=requestInput(0,1);
    int targetChoise;
    if (targetBoard==0){
        if(gamePtr->activePlayerIndex==0){ // most of this is just logic who is attacking who
            targetChoise=chooseTarget(gamePtr, 1);
            if(targetChoise==0){
                if(gamePtr->players[1]->takeHit(damage))
                    gamePtr->players[1]->isAlive=false;
            }else{
                if(gamePtr->players[1]->board.deck[targetChoise-1]->takeDmg(damage)){ // takeDmg returns 1 when damage kills creature
                    delete gamePtr->players[1]->board.deck[targetChoise-1];
                    gamePtr->players[1]->board.deck.erase(gamePtr->players[1]->board.deck.begin()+targetChoise-1);
                }
            }
        }else{
            targetChoise=chooseTarget(gamePtr, 0);
            if(targetChoise==0){
                if(gamePtr->players[0]->takeHit(damage))
                    gamePtr->players[0]->isAlive=false;
            }else{
                if(gamePtr->players[0]->board.deck[targetChoise-1]->takeDmg(damage)){ // takeDmg returns 1 when damage kills creature
                    delete gamePtr->players[0]->board.deck[targetChoise-1];
                    gamePtr->players[0]->board.deck.erase(gamePtr->players[0]->board.deck.begin()+targetChoise-1);
                }
            }
        }
    }else {
        if (gamePtr->activePlayerIndex == 0) {
            targetChoise = chooseTarget(gamePtr, 0);
            if(targetChoise==0){
                if(gamePtr->players[0]->takeHit(damage))
                    gamePtr->players[0]->isAlive=false;
            }else{
                if(gamePtr->players[0]->board.deck[targetChoise-1]->takeDmg(damage)){ // takeDmg returns 1 when damage kills creature
                    delete gamePtr->players[0]->board.deck[targetChoise-1];
                    gamePtr->players[0]->board.deck.erase(gamePtr->players[0]->board.deck.begin()+targetChoise-1);
                }
            }
        } else {
            targetChoise = chooseTarget(gamePtr, 1);
            if(targetChoise==0){
                if(gamePtr->players[1]->takeHit(damage))
                    gamePtr->players[1]->isAlive=false;
            }else {
                if(gamePtr->players[1]->board.deck[targetChoise-1]->takeDmg(damage)){ // takeDmg returns 1 when damage kills creature
                    delete gamePtr->players[1]->board.deck[targetChoise-1];
                    gamePtr->players[1]->board.deck.erase(gamePtr->players[1]->board.deck.begin()+targetChoise-1);
                }
            }
        }
    }
    return 0;
}

int attackAI(CGame* gamePtr, int damage) {
    srand(time(NULL));
    int enemyPlayerIndex;
    if(gamePtr->activePlayerIndex==0){
        enemyPlayerIndex=1;
    }else{
        enemyPlayerIndex=0;
    }

    int minionsOnOwnBoard=gamePtr->players[gamePtr->activePlayerIndex]->board.deck.size();
    int randomOwnMinionIndex=0;
    if(minionsOnOwnBoard>1){
        randomOwnMinionIndex=rand()%(minionsOnOwnBoard);
    }

    int minionsOnEnemyBoard=gamePtr->players[enemyPlayerIndex]->board.deck.size();
    int randomEnemyMinionIndex=0;
    if(minionsOnEnemyBoard>1){
        randomEnemyMinionIndex=rand()%(minionsOnEnemyBoard);
    }

    if(damage>=0){// it is healing
        // targetting own board, dice to minion or own health
        if(minionsOnOwnBoard){ // if has minions on board, decide else heal player
            if(rand()%2){// heals player
                gamePtr->players[gamePtr->activePlayerIndex]->takeHit(damage);
            }else{ // heals random minion
                gamePtr->players[gamePtr->activePlayerIndex]->board.deck[randomOwnMinionIndex]->takeDmg(damage);
            }
        }else{
            gamePtr->players[gamePtr->activePlayerIndex]->takeHit(damage);
        }
    }else{ // damaging
        if(minionsOnEnemyBoard){ // if has minions on board, decide else heal player
            if(rand()%2){// damages Player
                if(gamePtr->players[enemyPlayerIndex]->takeHit(damage)){
                    gamePtr->players[enemyPlayerIndex]->isAlive=false;
                }
            }else{ // damages random minion
                if(gamePtr->players[enemyPlayerIndex]->board.deck[randomEnemyMinionIndex]->takeDmg(damage)){
                    delete gamePtr->players[enemyPlayerIndex]->board.deck[randomEnemyMinionIndex];
                    gamePtr->players[enemyPlayerIndex]->board.deck.erase(gamePtr->players[enemyPlayerIndex]->board.deck.begin()+randomEnemyMinionIndex);
                }
            }
        }else{
            if(gamePtr->players[enemyPlayerIndex]->takeHit(damage))
                gamePtr->players[enemyPlayerIndex]->isAlive=false;
        }
    }
    return 0;
}


CBoard::CBoard(CGame & copy) : gamePtr(&copy) {

}

void CBoard::render() const {
    system("clear");
    int opponentIndex;
    if(gamePtr->activePlayerIndex==1)
        opponentIndex=0;
    else
        opponentIndex=1;

    char escChar='\033';
    string suffix="[0m";
    string greenprefix="[1;32m";// blue for minions
    string redprefix="[1;31m";// blue for minions

    cout << "You opponent's"<<escChar << redprefix <<" HP: "  << gamePtr->players[opponentIndex]->hp << escChar << suffix << ". He has " << gamePtr->players[opponentIndex]->hand.deck.size() <<" cards in hand and " << gamePtr->players[opponentIndex]->deck.deck.size() << " Cards in his deck." << endl;
    cout << "Opponent's board:" << endl;
    gamePtr->players[opponentIndex]->board.render();
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Your board:" << endl;
    gamePtr->players[gamePtr->activePlayerIndex]->board.render();
    cout << "Your" <<escChar << greenprefix <<  " HP: " << gamePtr->players[gamePtr->activePlayerIndex]->hp  << escChar << suffix << ", Your usable mana: " << gamePtr->players[gamePtr->activePlayerIndex]->availableMana << ", You have " << gamePtr->players[gamePtr->activePlayerIndex]->deck.deck.size()<< " Cards in your deck." << endl;
    cout << endl;
}

int CBoard::parseInput() {
    gamePtr->players[gamePtr->activePlayerIndex]->availableMana=10;

    if(!gamePtr->gameLoaded &&!gamePtr->players[gamePtr->activePlayerIndex]->deck.deck.empty() && gamePtr->players[gamePtr->activePlayerIndex]->hand.deck.size() < 7){
        gamePtr->players[gamePtr->activePlayerIndex]->hand.deck.push_back(gamePtr->players[gamePtr->activePlayerIndex]->deck.deck.back());// take a card from back of deck
        gamePtr->players[gamePtr->activePlayerIndex]->deck.deck.pop_back();
    }
    gamePtr->gameLoaded=false;


   if(typeid(*(gamePtr->players[gamePtr->activePlayerIndex]))==typeid(CHumanPlayer)){ // human player
       CPlayer* currentHumanPlayer=gamePtr->players[gamePtr->activePlayerIndex];
       if(gamePtr->players[gamePtr->activePlayerIndex]->hand.deck.size()>=7){ // too many cards
           cout<< "You have the maximum amount of cards in your hand." << endl;
       }else if(gamePtr->players[gamePtr->activePlayerIndex]->deck.deck.size()==0){// no more cards in deck
           cout << "You have no more cards in your deck." << endl;
       }

       while (true){
           int enemyPlayerIndex;
           if(gamePtr->activePlayerIndex==0){
               enemyPlayerIndex=1;
           }else{
               enemyPlayerIndex=0;
           }

           if(!gamePtr->players[gamePtr->activePlayerIndex]->isAlive ){ // end game checker
               system("clear");
               return 1;
           }else if(!gamePtr->players[enemyPlayerIndex]->isAlive){
               system("clear");
               return 1;
           }

           cout<< "Here are your cards in your hand:" << endl;
           currentHumanPlayer->hand.render();
           cout << "[1] Play a card" << endl;
           cout << "[2] End turn + Attack with Minions" << endl;
           cout << "[3] Pause menu" << endl;
           cout << "What do you wish to do ?: " << flush;
           int selection = requestInput(0,3);
           switch(selection){
               case 1:{
                   int playerInput=0;
                   cout<< "Enter card to play, to go back to previous menu enter '-1': " << endl;
                   do{
                       playerInput=requestInput(-1, currentHumanPlayer->hand.deck.size());
                       if (playerInput>=0 && playerInput<currentHumanPlayer->hand.deck.size()){

                           if(currentHumanPlayer->hand.deck[playerInput]->manaRequired <= currentHumanPlayer->availableMana){ // subtracting mana
                               currentHumanPlayer->availableMana-=currentHumanPlayer->hand.deck[playerInput]->manaRequired;
                               // create a real card on the battlefield if minion, else apply spell
                               if(!currentHumanPlayer->hand.deck[playerInput]->isSpell){
                                   currentHumanPlayer->board.deck.push_back(currentHumanPlayer->hand.deck[playerInput]->clone());
                                   currentHumanPlayer->hand.deck.erase(currentHumanPlayer->hand.deck.begin()+playerInput);
                                   this->render();
                                   break;
                               }else{// cast spell
                                   cout << "Who do you want to target with "<< currentHumanPlayer->hand.deck[playerInput]->name << ", Desc: " << currentHumanPlayer->hand.deck[playerInput]->description<< "?" << endl;
                                   attack(gamePtr, currentHumanPlayer->hand.deck[playerInput]->apply());
                                   currentHumanPlayer->hand.deck.erase(currentHumanPlayer->hand.deck.begin()+playerInput);
                                   this->render();
                                   break;
                               }
                           }else{
                               cout<< "You do not have enough mana to summon this."<< endl;
                           }
                       }
                   }while(playerInput != -1);
                   continue;
               }
               case 2:{ // ending turn
                   for(int i=0; i<gamePtr->players[gamePtr->activePlayerIndex]->board.deck.size(); i++){
                       cout << "Your ";
                       gamePtr->players[gamePtr->activePlayerIndex]->board.deck[i]->render();
                       cout << "is attacking. Please enter its target." << endl;
                       attack(gamePtr, gamePtr->players[gamePtr->activePlayerIndex]->board.deck[i]->apply());
                   }
                   system("clear");
                   cout << "You ended your turn." << endl;
                   return 2;
               }
               case 3:{ // go to pause menu
                   return 3;
               }
               default:{
                   cout << "incorrect option. Please retry: " << endl;
                   continue;
               }
           }
       }
   }else{ // AI player
       /**
        * 1. Checks how many cards it has
        * 2. Chooses a card, checks if it has enough mana to cast it
        * 3a. Its a minion, puts it on board, continues to look for more cards
        * 3b. Its a spell, checks if healing or damaging, if damaging - enemy face or minions, if healing yourself or minions
        * 4. Ends turn, attacks face or minions
        */
       CPlayer* currentAIPlayer=gamePtr->players[gamePtr->activePlayerIndex];
        while(true){
            int enemyPlayerIndex;
            if(gamePtr->activePlayerIndex==0){
                enemyPlayerIndex=1;
            }else{
                enemyPlayerIndex=0;
            }


            if(currentAIPlayer->hand.deck.size()){ // if has cards consider them
                for(int i =0 ; i<currentAIPlayer->hand.deck.size() ; i++){
                    if(currentAIPlayer->hand.deck[i]->manaRequired<=currentAIPlayer->availableMana){ // has enough mana
                        currentAIPlayer->availableMana-=currentAIPlayer->hand.deck[i]->manaRequired; // subtracts mana
                        if(currentAIPlayer->hand.deck[i]->isSpell) {// its a spell
                            if(attackAI(gamePtr, currentAIPlayer->hand.deck[i]->apply())){
                                return 1;
                            }
                            currentAIPlayer->hand.deck.erase(currentAIPlayer->hand.deck.begin()+i);
                            break;
                        }else{ // it is a minion
                            currentAIPlayer->board.deck.push_back(currentAIPlayer->hand.deck[i]->clone());
                            currentAIPlayer->hand.deck.erase(currentAIPlayer->hand.deck.begin()+i);
                            break;
                        }
                    }
                    if(i+1 >=currentAIPlayer->hand.deck.size()){ // Has considered all the cards, end turn
                        for(int i=0; i<gamePtr->players[gamePtr->activePlayerIndex]->board.deck.size(); i++){
                            attackAI(gamePtr, gamePtr->players[gamePtr->activePlayerIndex]->board.deck[i]->apply());
                        }
                        system("clear");
                        cout << "AI has ended Its Turn" << endl;

                        return 2;
                    }
                }
            }else{
                for(int i=0; i<gamePtr->players[gamePtr->activePlayerIndex]->board.deck.size(); i++){
                    attackAI(gamePtr, gamePtr->players[gamePtr->activePlayerIndex]->board.deck[i]->apply());
                }
                system("clear");
                cout << "AI has ended Its Turn" << endl;
                return 2;
            }
        }

   }
   return 0;
}


