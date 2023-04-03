#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;
Game::Game(){

}
Game::Game(Player p1,Player p2){
    this->playerOne=p1;
    this->PlayerTwo=p2;
    this->gameDone=true;
    this->winner=false;
    this->createCards();
    this->shuffleCards();
}
void Game:: playTurn(){
    return;
}
void Game:: printLastTurn(){
    return;
}
void Game:: playAll(){
    return;
}
void Game:: printWiner(){
    return;
}
void Game:: printLog(){
    return;
}
void Game:: printStats(){
    return;
}
Player Game:: getWinner(){
    return this->playerOne;
}
bool Game:: isDone(){
    return false;;
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
}
void Game:: shuffleCards(){
    
}

// for (size_t i = 0; i < 52; i++)
//     {
//         cout<< this->cards[i].toString()<<std::endl;       
//     }