//
// Created by mintsdz on 4/9/23.
//

#ifndef CARDWARGAME_PLAYER_HPP
#define CARDWARGAME_PLAYER_HPP


#include "card.hpp"
#include <stack>
#include <string>

class Player{
private:
    std::string name;
    std::stack <Card> cardsPile;
    std::stack <Card> cardsTaken;
    unsigned int turnsPlayed;
    unsigned int turnsWon;
    unsigned int draws;
public:
    Player();
    Player(std::string);
    void addCardPile(Card);
    void addCardTaken(Card);
    int cardesTaken();
    int stacksize();
    void incrTurnsPlayed();
    void incrTurnsWon();
    void incrDraws();
    void printStats();
    Card pullCard();
    std::string getName();
};


#endif //CARDWARGAME_PLAYER_HPP
