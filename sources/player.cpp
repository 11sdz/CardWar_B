//
// Created by mintsdz on 4/9/23.
//

#include "player.hpp"
#include <string>
#include <iostream>

using namespace std;
/**
 * Constructor Player
 * @param pName player Name string/chars[]
 */
Player::Player (string pName){
    this->name=pName;
    this->turnsPlayed=0;
    this->turnsWon=0;
    this->draws=0;
}
Player::Player(){

}
/**
 * adding card to player cardPile
 * @param c Card
 */
void Player:: addCardPile(Card c){
    Card copy=c;
    this->cardsPile.push(copy);
    return;
}
/**
 * pulling a card to play
 * @return Card
 */
Card Player:: pullCard(){
    Card c=this->cardsPile.top();
    this->cardsPile.pop();
    return c;
}
/**
 * adding card taken to player's deck won pile
 * @param c card
 */
void Player::addCardTaken(Card c){
    Card copy=c;
    this->cardsTaken.push(copy);
    return;
}
/**
 * amount of deck taken
 * @return integer cardsTaken size
 */
int Player:: cardesTaken(){
    return cardsTaken.size();
}
/**
 * amount of deck ready to play
 * @return integer cardsPile size
 */
int Player:: stacksize(){
    return cardsPile.size();
}
/**
 * increase turnsPlayed counter
 */
void Player:: incrTurnsPlayed(){
    this->turnsPlayed++;
    return;
}
/**
 * increase turnsWon counter
 */
void Player:: incrTurnsWon(){
    this->turnsWon++;
    return;
}
/**
 * increase turnsDraws counter
 */
void Player:: incrDraws(){
    this->draws++;
    return;
}/**
 * calculate and print playerStats
 */
void Player:: printStats(){
    cout << "====== " + name + " Game stats======" << endl;
    if(turnsPlayed>0) {
        float winRate = (float) turnsWon / turnsPlayed;
        float drawRate = (float) draws / turnsPlayed;
        float cardsPerTurn = (float) cardesTaken() / turnsPlayed;
        cout << "Win Rate: " + to_string(winRate);
        cout << " . Draw Rate: " + to_string(drawRate) << endl;
        cout << "Cards Taken: " + to_string(cardesTaken()) + " .Cards taken per turn: " + to_string(cardsPerTurn);
        cout << " . turns played: " + to_string(turnsPlayed) + "\n" << endl;
        return;
    }
    cout << "the Game hasn't started"<< endl;
    return;
}
std::string Player:: getName(){
    return this->name;
}