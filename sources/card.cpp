#include "card.hpp"
Card::Card(cardType cardType,int value){
    this->type=cardType;
    this->value=value;
}
Card::Card(){
    
}
int Card:: getValue(){
    return this->value;
}
std::string Card::toString(){
    std::string cardString=valueNames[(size_t)this->value]+(" of ")+cTypeNames[this->type];
    return cardString;
}