#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
#include <iterator>
#include <time.h>
using namespace std;
Game::Game(){

}
Game::Game(Player p1,Player p2){
    this->playerOne=p1;
    this->playerTwo=p2;
    this->gameDone=false;
    this->winner=0;
    this->createCards();
    this->shuffleCards();
    this->turnCounter=0;
}
void Game:: playTurn(){
    if(!gameDone){
        string log;
        turnCounter++;
        playerOne.incrTurnsPlayed();
        playerTwo.incrTurnsPlayed();
        Card cardP1 = this->playerOne.pullCard();
        Card cardP2 = this->playerTwo.pullCard();
        int diff=cardP1.getValue()-cardP2.getValue();
        if(diff==0){//Draw
            playerOne.incrDraws();
            playerTwo.incrDraws();
            bool eFlag=false;
            stack <Card> cs;
            cs.push(cardP1);
            cs.push(cardP2);
            int numOfCards=1;
            while(!(cs.empty())){
                if(playerOne.stacksize()>1){
                    log.append(this->turnString(playerOne.getName(),playerTwo.getName()
                                            ,cardP1.toString(),cardP2.toString()));
                    log.append(" Draw.\n drawing flipped card ");
                    cs.push(playerOne.pullCard());
                    cs.push(playerTwo.pullCard());
                    cardP1=playerOne.pullCard();
                    cardP2=playerTwo.pullCard();
                    diff=cardP1.getValue()-cardP2.getValue();
                    if(diff!=0){
                        int winner = this->getRoundWinner(diff,cardP1,cardP2);
                        if(winner==1){
                            playerOne.addCardTaken(cardP1);
                            playerOne.addCardTaken(cardP2);
                            log.append(this->turnString(playerOne.getName(),playerTwo.getName()
                                            ,cardP1.toString(),cardP2.toString()));
                            log.append(playerOne.getName()+" win .");
                            while(!cs.empty()){
                                playerOne.addCardTaken(cs.top());
                                cs.pop();
                            }
                            playerOne.incrTurnsWon();
                        }else if(winner==2){
                            playerTwo.addCardTaken(cardP1);
                            playerTwo.addCardTaken(cardP2);
                            log.append(this->turnString(playerOne.getName(),playerTwo.getName()
                                            ,cardP1.toString(),cardP2.toString()));
                            log.append(playerTwo.getName()+" win .");
                            playerTwo.incrTurnsWon();
                            while(!cs.empty()){
                                playerTwo.addCardTaken(cs.top());
                                cs.pop();
                            }
                        }
                    }
                    numOfCards+=2;
                }else if(playerOne.stacksize()==1){
                    cs.push(playerOne.pullCard());
                    cs.push(playerTwo.pullCard());
                    numOfCards++;
                    eFlag=true;
                    break;
                }else{
                    eFlag=true;
                    break;
                }
                if(eFlag){
                    //cards ended for bothsides
                    while(!cs.empty()){
                        playerOne.addCardTaken(cs.top());
                        cs.pop();
                        playerTwo.addCardTaken(cs.top());
                        cs.pop();
                    }
                }
            }
            log.append("Cards Won =");
            log.append(to_string(numOfCards));
        }else{// round ended with a Win
            int winner = this->getRoundWinner(diff,cardP1,cardP2);
            if(winner==1){
                playerOne.addCardTaken(cardP1);
                playerOne.addCardTaken(cardP2);
                log.append(this->turnString(playerOne.getName(),playerTwo.getName()
                                            ,cardP1.toString(),cardP2.toString()));
                log.append(playerOne.getName()+" win ");
                playerOne.incrTurnsWon();
            }else if(winner==2){
                playerTwo.addCardTaken(cardP1);
                playerTwo.addCardTaken(cardP2);
                log.append(this->turnString(playerOne.getName(),playerTwo.getName()
                                            ,cardP1.toString(),cardP2.toString()));
                log.append(playerTwo.getName()+" win ");
                playerTwo.incrTurnsWon();
            }
        }
        if(playerOne.stacksize()==0 && playerTwo.stacksize()==0){
            gameDone=true;
        }
        slogger.push(log);
        qlogger.push(log);
    }
}
string Game::turnString(string name1,string name2, string card1,string card2){
    string str;
    str.append(name1+" has played "+card1+" "+name2+" has played "+card2+" ,");
    return str;
}
int Game::getRoundWinner(int diff,Card cardP1,Card cardP2){
        if(diff>0){//PlayerOne got higher card
            if(cardP2.getValue()!=1){
                // playerOne got higher card and playerTwo didnt played Ace
                return 1;
            }else if(cardP1.getValue()!=2 && cardP2.getValue()==1){
                // playerTwo got Ace
                return 2;
            }
        }else{//PlayerTwo got higher card
            if(cardP1.getValue()!=1){
                //PlayerTwo got higher card and playerOne didnt played Ace
                return 2;
            }else if(cardP2.getValue()!=2 && cardP1.getValue()==1){
                //PlayerOne got Ace
                return 1;
            }
        }
    return -1;
}
void Game:: printLastTurn(){
    cout<<slogger.top()<<endl;
    return;
}
void Game:: playAll(){
    while(!gameDone){
        playTurn();
    }
    return;
}
void Game:: printWiner(){
    int c1 = playerOne.cardesTaken();
    int c2 = playerTwo.cardesTaken();
    int diff = c1-c2;
    if(diff==0){
        cout<<"Game Ends Draw"<<endl;
    }else if(diff>0){
        cout<<playerOne.getName()+" has Won the Game gg" <<endl;
    }else{
        cout<<playerTwo.getName()+" has Won the Game gg" <<endl;
    }
    return;
}
void Game:: printLog(){
    while(!qlogger.empty()){
        cout<<qlogger.front()<<endl;
        qlogger.pop();
    }
    return;
}
void Game:: printStats(){
    return;
}
Player Game:: getWinner(){
    return this->playerOne;
}
bool Game:: isDone(){
    return gameDone;
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
    size_t counter=0;
    //srand((unsigned int) time(NULL));
    srand(100);
    float result;
    while(playerOne.stacksize()<26 && playerTwo.stacksize()<=26){
        result = (float) rand()/2147483648;
        cout<<result<<endl;
        if(result<0.5){
            playerOne.addCardPile(cards[counter++]);
        }else{
            playerTwo.addCardPile(cards[counter++]);
        }
    }
    while(playerOne.stacksize()<26){
        playerOne.addCardPile(cards[counter++]);
    }
    while(playerTwo.stacksize()<26){
        playerTwo.addCardPile(cards[counter++]);
    }
}

// for (size_t i = 0; i < 52; i++)
//     {
//         cout<< this->cards[i].toString()<<std::endl;       
//     }