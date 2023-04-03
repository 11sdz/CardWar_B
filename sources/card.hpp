#ifndef CARD_H
#define CARD_H
#include <string>
enum cardType{redDiamond=0,redHeart=1,blackSpade=2,blackClub=3};
static const std::string cTypeNames[]={"Red Diamond","Red Heart","Black Spade","Black Club"};
static const std::string valueNames[]={"FILLER","Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Prince","Queen","King"};
class Card{
    private:
        int value;
        cardType type;
    public:
        Card();
        Card(cardType,int);
        int getValue();
        std::string toString();
};
#endif