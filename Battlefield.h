#include <iostream>
#include "card.h"

class Battlefield{
    public:
    Battlefield();
    void AddCard(card& newCard, bool support=true, int slot=-1);
    void RemoveCard(int slot, bool support=true);

    private:
    typedef struct {int index; card* _card;} cardIndex;
    const vector<sf::Vector2f> battlePositions = {{100,100}, {200,100}};
    const vector<sf::Vector2f> supportPositions = {{ 75,200}, {125,200}, {175,200}, {225,200}}; 
    vector<cardIndex> supportCards;
    vector<cardIndex> battleCards;
    const int MAX_SUPPORT_CARDS = 4;
    const int MAX_BATTLE_CARDS = 2;
    int getNextFreeSlot(vector<cardIndex>& cards, int max);
    card* getCardAt(int slot, int& inIndex, bool support=true);
};