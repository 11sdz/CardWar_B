#ifndef GAME_H
#define GAME_H
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
class Game{
    private:
        Player playerOne;
        Player playerTwo;
        std::array<Card,totalCards>cards;
        bool gameDone;
        int winner;
        std::stack<std::string> slogger;
        std::queue<std::string> qlogger;

        void createCards();
        void shuffleCards();
        int turnCounter;
        std::string turnString(string,string,string,string);
        int getRoundWinner(int,Card,Card);

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