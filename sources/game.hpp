//
// Created by mintsdz on 4/9/23.
//

#ifndef CARDWARGAME_GAME_HPP
#define CARDWARGAME_GAME_HPP


#include "player.hpp"
#include "card.hpp"
#include <list>
#include <string>
#include <array>
#include <queue>
static const int totalCards=52;
using namespace std;
namespace ariel{

}
/**
 * Class Game of CardWar
 * contains 2 players pointers
 * deck array of 52 french suited cards, shuffle array of 52 indexes 0-52
 * list logger storing each turn string
 */
class Game{
private:
    Player* playerOne;
    Player* playerTwo;
    std::array<Card,totalCards>deck;
    std::array<size_t,totalCards>shuffle;
    bool gameDone;
    std::list<std::string> logger;
    void createCards();
    void shuffleCards();
    int turnCounter;
    std::string turnString(string,string,string,string);
    int getRoundWinner(int,Card,Card);

public:
    Game();
    Game(Player&,Player&);
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
};
#endif //CARDWARGAME_GAME_HPP
