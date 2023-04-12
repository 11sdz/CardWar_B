//
// Created by mintsdz on 4/9/23.
//

#ifndef CARDWARGAME_PLAYER_HPP
#define CARDWARGAME_PLAYER_HPP


#include "card.hpp"
#include <stack>
#include <string>

/**
 * class Player represents player
 * each player has a 2 stacks (LIFO) that represents his cardsPile, and cardsTaken the deck won through the game
 * for saving his stats through the game player has basic methods to count turns played,turns won , draws.
 */
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
