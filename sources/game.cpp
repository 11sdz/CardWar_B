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
/**
 * Game constructor
 * initialize game deck ,shuffling between players;
 * @param p1 player reference
 * @param p2 player reference
 */
Game::Game(Player &p1,Player &p2){
    this->playerOne=&p1;
    this->playerTwo=&p2;
    this->gameDone=false;
    this->createCards();
    this->shuffleCards();
    this->turnCounter=0;
}
/**
 * playing the turn until we get winner
 * the winner collect all cards
 * string @log represents the turn to_string that stored in the @logger
 * ("Turn number ##: name1 has played card1 name2 has played card2 ,(name1/name2 Win)/(Draw)")
 * stack @cs every card pulled is being pushed to the stack the winner get all the cards in the stack
 * (if draw and no more cards players collect their own cards)
 */
void Game::playTurn() {
    if(playerOne==playerTwo){
        throw string("duplicate players : player cant play against himself");
    }
    //first draw meaning we dont count another turn if more then 1 draw has made
    bool firstDraw=true;
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
            //using method getRoundWinner by calculating the different between the cards values to get the winner
            // 0 - for draw , 1 - playerOne won , 2 -  playerTwo won
            int roundWinner = getRoundWinner(cardP1.getValue() - cardP2.getValue(), cardP1, cardP2);
            if (roundWinner == 0) {
                if(firstDraw) {
                    playerOne->incrDraws();
                    playerTwo->incrDraws();
                    firstDraw=false;
                }
                log.append(turnString(playerOne->getName(),playerTwo->getName(),cardP1.toString(),cardP2.toString()));
                log.append(" Draw \n");
                if(playerTwo->stacksize()<2 && playerOne->stacksize()<2){
                    //draw cannot continue not enough cards players will collect their own cards
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
                    log.append("no more cards players collect own cards , game ends\n");
                    gameDone = true;
                    break;
                }
                //in case of draw each player pull flipped card get pushed straight to the winnerStack @cs
                cs.push(playerOne->pullCard());
                cs.push(playerTwo->pullCard());
                //each player pull card to determinate the winner
                cardP1 = playerOne->pullCard();
                cardP2 = playerTwo->pullCard();
                cs.push(cardP1);
                cs.push(cardP2);
                amountOfCards+=2;
                cardsWon= "("+to_string(amountOfCards)+" cards)";
            }
            else {
                //there is a winner who collects all cards in @cs winner stack
                while (!cs.empty()) {
                    if (roundWinner == 1) {
                        playerOne->addCardTaken(cs.top());
                        cs.pop();
                        name=playerOne->getName();
                    } else {
                        playerTwo->addCardTaken(cs.top());
                        cs.pop();
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
                    //case of no more cards game ends!
                    gameDone= true;
                }
            }
        }
        logger.insert(logger.cend(),log);
    }else{
        throw string ("Game is Over All turns played");
    }
}

/**
 *
 * @param name1 playerOne name string
 * @param name2 playerTwo name string
 * @param card1 card of playerOne string
 * @param card2 card of PlayerTwo string
 * @return "name1 has played card1 name2 has played card2"
 */
string Game::turnString(string name1,string name2, string card1,string card2){
    string str;
    str.append(name1+" has played "+card1+" "+name2+" has played "+card2+" ,");
    return str;
}
/**
 * method to determinate the winner by game rules
 * 1.higher value wins
 * 2."Ace"=1 is strong against all values besides 2
 * @param diff (playerOne card1 value) - (playerTwo card2 value)
 *        if positive diff>0 playerTwo can win only if he drew "Ace"=1 and PlayerOne didnt drew "Two"=2.
 *        if negative diff<0 playerOne can win only if he drew "Ace"=1 and playerTwo didnt drew "Two"=2.
 *        if diff=0 then cards values equal we return 0
 * @param cardP1 represents the card drew by playerOne
 * @param cardP2 represents the card drew by playerTwo
 * @return 0 - draw , 1 - playerOne won, 2 playerTwo won.
 */
int Game::getRoundWinner(int diff,Card cardP1,Card cardP2){
    if(diff>0){//PlayerOne got higher card
        switch (cardP2.getValue()) {
            case 1:
                if (diff==1){
                    return 1;
                }
                return 2;
            default:
                return 1;
        }
    }else if(diff<0){//PlayerTwo got higher card
        switch (cardP1.getValue()) {
            case 1:
                if (diff==-1) {
                    return 2;
                }
                return 1;
            default:
                return 2;
        }
    }
    return 0;
}
/**
 * prints the latest string(log in playTurn()) in the @logger list
 */
void Game:: printLastTurn(){
    list<string>::iterator it=logger.end();
    it--;
    cout<<it->data()<<endl;
    return;
}
/**
 * playing all turns automatically
 * by calling playTurn() each time until gameDone is true
 */
void Game:: playAll(){
    while(!gameDone){
        playTurn();
    }
    return;
}
/**
 * printing the winner of the game, or draw if it is
 * "(player's name) has Won the Game gg"/"Game Ends Draw"
 */
void Game:: printWiner(){
    int c1 = playerOne->cardesTaken();
    int c2 = playerTwo->cardesTaken();
    int diff = c1-c2;
    if(diff==0){
        cout<<"Game Ends Draw"<<endl;
    }else if(diff>0){
        cout<<playerOne->getName()+" has Won the Game gg" <<endl;
    }else{
        cout<<playerTwo->getName()+" has Won the Game gg" <<endl;
    }
    return;
}
/**
 * printing @logger strings
 * representing all the turns that has played
 */
void Game:: printLog(){
    for (list<string>::iterator it=logger.begin();it!=logger.end();++it){
        cout<<it->data()<<endl;
    }
    return;
}
/**
 * printing each player stats in this game
 */
void Game:: printStats(){
    playerOne->printStats();
    playerTwo->printStats();
    return;
}
/**
 *creating the deck french suited playing cards
 * [Ace of red Diamond,Ace of red Heart,Ace of black Spade,Ace of black Club,.....
 * ....King of Diamond, King of Heart,King of Spade,king of Club] 52 total
 * shuffle array[0,1,2,3...51]
 */
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

        this->deck[id++]=redDiamond;
        this->deck[id++]=redHeart;
        this->deck[id++]=blackSpade;
        this->deck[id++]=blackClub;
    }
    for (size_t i = 0; i <totalCards ; ++i) {
        shuffle[i]=i;
    }
}
/**
 * shuffling the shuffle array indexes from sorted [0,1,2....51] to unsorted
 * then deal the cards by the random unsorted indexes
 */
void Game:: shuffleCards(){
    srand((unsigned int) time(NULL));
    for (size_t i = 0; i < this->shuffle.size() ; ++i) {
        size_t temp,j= (size_t) rand()%totalCards;
        temp = shuffle[i];
        shuffle[i]=shuffle[j];
        shuffle[j]=temp;
    }
    for (size_t i = 0,j=1 ;(i <totalCards) && (j<totalCards) ; i+=2,j+=2) {
        playerOne->addCardPile(deck[shuffle[i]]);
        playerTwo->addCardPile((deck[shuffle[j]]));
    }
}