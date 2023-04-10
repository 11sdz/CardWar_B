//
// Created by mintsdz on 4/9/23.
//

#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;
Game::Game(){

}
Game::Game(Player &p1,Player &p2){
    this->playerOne=&p1;
    this->playerTwo=&p2;
    this->gameDone=false;
    this->winner=0;
    this->createCards();
    this->shuffleCards();
    this->turnCounter=0;
}
void Game::playTurn() {
    if(playerOne==playerTwo){
        throw string("duplicate players : player cant play against himself");
    }
    if(!gameDone) {
        turnCounter++;
        string log;
        stack<Card> cs;
        string name="",cardsWon="";
        int amountOfCards=2;
        playerOne->incrTurnsPlayed();
        playerTwo->incrTurnsPlayed();
        Card cardP1 = playerOne->pullCard();
        Card cardP2 = playerTwo->pullCard();
        log.append("Turn number "+to_string(turnCounter)+": ");
        cs.push(cardP1);
        cs.push(cardP2);
        bool turnEnd=false;
        while(!turnEnd) {
            int roundWinner = getRoundWinner(cardP1.getValue() - cardP2.getValue(), cardP1, cardP2);
            if (roundWinner == 0) {
                playerOne->incrDraws();
                playerTwo->incrDraws();
                log.append(turnString(playerOne->getName(),playerTwo->getName(),cardP1.toString(),cardP2.toString()));
                log.append(" Draw \n");
                if(playerTwo->stacksize()<2 && playerOne->stacksize()<2){
                    if(playerOne->stacksize()==1 && playerTwo->stacksize()==1){
                        playerOne->addCardTaken(playerOne->pullCard());
                        playerTwo->addCardTaken(playerTwo->pullCard());
                    }
                    while(!cs.empty()) {
                        playerOne->addCardTaken(cs.top());
                        cs.pop();
                        playerTwo->addCardTaken(cs.top());
                        cs.pop();
                    }
                    turnEnd = true;
                    gameDone = true;
                    break;
                }
                cs.push(playerOne->pullCard());
                cs.push(playerTwo->pullCard());
                cardP1 = playerOne->pullCard();
                cardP2 = playerTwo->pullCard();
                cs.push(cardP1);
                cs.push(cardP2);
                amountOfCards+=2;
                cardsWon= "("+to_string(amountOfCards)+" cards)";
            } else {
                while (!cs.empty()) {
                    if (roundWinner == 1) {
                        playerOne->addCardTaken(cs.top());
                        cs.pop();
                        name=playerOne->getName();
                    } else {
                        playerTwo->addCardTaken(cs.top());
                        cs.pop();
                        playerTwo->incrTurnsWon();
                        name=playerTwo->getName();
                    }
                }
                if(roundWinner==1){
                    playerOne->incrTurnsWon();
                }else if(roundWinner ==2){
                    playerTwo->incrTurnsWon();
                }
                log.append(turnString(playerOne->getName(),playerTwo->getName(),cardP1.toString(),cardP2.toString()));
                log.append(name+" Win "+cardsWon);
                turnEnd= true;
                if((playerOne->stacksize()==0) && (playerTwo->stacksize()==0)){
                    gameDone= true;
                }
            }
        }
        slogger.push(log);
        qlogger.push(log);
    }else{
        throw string ("Game is Over All turns played");
    }
}


string Game::turnString(string name1,string name2, string card1,string card2){
    string str;
    str.append(name1+" has played "+card1+" "+name2+" has played "+card2+" ,");
    return str;
}
int Game::getRoundWinner(int diff,Card cardP1,Card cardP2){
    if(diff>0){//PlayerOne got higher card
        if(cardP2.getValue()!=1){
            // playerOne got higher card and playerTwo didnt played Ace
            return 1;
        }else if(cardP1.getValue()!=2 && cardP2.getValue()==1){
            // playerTwo got Ace
            return 2;
        }
    }else if(diff<0){//PlayerTwo got higher card
        if(cardP1.getValue()!=1){
            //PlayerTwo got higher card and playerOne didnt played Ace
            return 2;
        }else if(cardP2.getValue()!=2 && cardP1.getValue()==1){
            //PlayerOne got Ace
            return 1;
        }
    }
    return 0;
}
void Game:: printLastTurn(){
    cout<<slogger.top()<<endl;
    return;
}
void Game:: playAll(){
    while(!gameDone){
        playTurn();
    }
    return;
}
void Game:: printWiner(){
    int c1 = playerOne->cardesTaken();
    int c2 = playerTwo->cardesTaken();
    int diff = c1-c2;
    if(diff==0){
        cout<<"Game Ends Draw"<<endl;
        throw string("Draw no winner");
    }else if(diff>0){
        cout<<playerOne->getName()+" has Won the Game gg" <<endl;
    }else{
        cout<<playerTwo->getName()+" has Won the Game gg" <<endl;
    }
    return;
}
void Game:: printLog(){
    while(!qlogger.empty()){
        cout<<qlogger.front()<<endl;
        qlogger.pop();
    }
    return;
}
void Game:: printStats(){
    playerOne->printStats();
    playerTwo->printStats();
    return;
}
bool Game:: isDone(){
    return gameDone;
}
void Game:: createCards(){
    size_t id=0;
    for (int i = 1; i <= 13; i++)
    {
        cardType type=redDiamond;
        Card redDiamond(type,i);
        type=redHeart;
        Card redHeart(type,i);
        type=blackSpade;
        Card blackSpade(type,i);
        type=blackClub;
        Card blackClub(type,i);

        this->cards[id++]=redDiamond;
        this->cards[id++]=redHeart;
        this->cards[id++]=blackSpade;
        this->cards[id++]=blackClub;
    }
    for (size_t i = 0; i <totalCards ; ++i) {
        shuffle[i]=i;
    }
}
void Game:: shuffleCards(){
    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < this->shuffle.size() ; ++i) {
        size_t temp,j= (size_t) rand()%totalCards;
        temp = shuffle[i];
        shuffle[i]=shuffle[j];
        shuffle[j]=temp;
    }
    for (size_t i = 0,j=1 ;(i <totalCards) && (j<totalCards) ; i+=2,j+=2) {
        playerOne->addCardPile(cards[shuffle[i]]);
        playerTwo->addCardPile((cards[shuffle[j]]));
    }
}

// for (size_t i = 0; i < 52; i++)
//     {
//         cout<< this->cards[i].toString()<<std::endl;
//     }