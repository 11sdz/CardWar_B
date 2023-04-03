#include "player.hpp"
#include <string>
#include <iostream>
Player::Player (std::string pName){
    this->name=pName;
    this->turnsPlayed=0;
    this->turnsWon=0;
    this->draws=0;
}
Player::Player(){
    
}
void Player:: addCardPile(Card c){
    this->cardsPile.push(c);
    return;
}
Card Player:: pullCard(){
    Card c=this->cardsPile.top();
    this->cardsPile.pop();
    return c;
}
void Player::addCardTaken(Card c){
    this->cardsTaken.push(c);
    return;
}
int Player:: cardesTaken(){
    return this->cardsTaken.size();
}
int Player:: stacksize(){
    return this->cardsPile.size();
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
    std::cout<<"hello stats"<<std::endl;
    return;
}