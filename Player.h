#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>

using namespace std;

class Player{
    private:
    list<card*> deck;
    list<card*> hand;    
    list<card*> graveyard;

    public:
    void drawCards(const int count);
    void playCard(card* card);
};