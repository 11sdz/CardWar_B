//
// Created by mintsdz on 4/9/23.
//

#include "player.hpp"
#include <string>
#include <iostream>

using namespace std;
Player::Player (string pName){
    this->name=pName;
    this->turnsPlayed=0;
    this->turnsWon=0;
    this->draws=0;
}
Player::Player(){

}
void Player:: addCardPile(Card c){
    Card copy=c;
    this->cardsPile.push(copy);
    return;
}
Card Player:: pullCard(){
    Card c=this->cardsPile.top();
    this->cardsPile.pop();
    return c;
}
void Player::addCardTaken(Card c){
    Card copy=c;
    this->cardsTaken.push(copy);
    return;
}
int Player:: cardesTaken(){
    return cardsTaken.size();
}
int Player:: stacksize(){
    return cardsPile.size();
}
void Player:: incrTurnsPlayed(){
    this->turnsPlayed++;
    return;
}
void Player:: incrTurnsWon(){
    this->turnsWon++;
    return;
}
void Player:: incrDraws(){
    this->draws++;
    return;
}
void Player:: printStats(){
    float winRate=(float)turnsWon/turnsPlayed;
    float drawRate=(float)draws/turnsPlayed;
    float cardsPerTurn= (float)cardesTaken()/turnsPlayed;
    cout<<"====== "+name+" Game stats======"<<endl;
    cout<<"Win Rate: "+to_string(winRate);
    cout<<" . Draw Rate: "+to_string(drawRate)<<endl;
    cout<<"Cards Taken: "+to_string(cardesTaken())+" .Cards taken per turn: "+to_string(cardsPerTurn);
    cout<<" . turns played: "+to_string(turnsPlayed)+"\n"<<endl;

    return;
}
std::string Player:: getName(){
    return this->name;
}