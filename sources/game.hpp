#ifndef GAME_H
#define GAME_H
#include "player.hpp"
#include "card.hpp"
#include <stack>
#include <string>
#include <array>
static const int totalCards=52;
using namespace std;
namespace ariel{
    
}
class Game{
    private:
        Player playerOne;
        Player PlayerTwo;
        std::array<Card,totalCards>cards;
        bool gameDone;
        bool winner;
        std::stack <std::string> logger;
        void createCards();
        void shuffleCards();

    public:
        Game();
        Game(Player,Player);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        Player getWinner();
        bool isDone();
};
#endif