//
// Created by mintsdz on 4/9/23.
//

#ifndef CARDWARGAME_CARD_HPP
#define CARDWARGAME_CARD_HPP


#include <string>
#include <array>
/**
 *  enum @cardType for the 4 common french suited playing deck <Red Diamonds ,Red Hearts , Black Spades, Bloack Clubs>
 *  const array @cTypeNames contains strings each string suitable for a to_string of the enum @CardType
 *  const array @valueNames contains strings each string suitable for the values 1-13 Ace,2,3...,KING. [0-12]
 *  */
enum cardType{redDiamond=0,redHeart=1,blackSpade=2,blackClub=3};
static const std::array<std::string,4> cTypeNames={"Red Diamond","Red Heart","Black Spade","Black Club"};
static const std::array<std::string,14> valueNames={"Ace","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Prince","Queen","King"};
/**
 * class Card represent card, has value and type
 */
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


#endif //CARDWARGAME_CARD_HPP
