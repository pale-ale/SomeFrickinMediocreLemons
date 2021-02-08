#pragma once

#include <iostream>
#include "card.h"
#include "Placeable.h"

class Battlefield : public Placeable{
    public:
    Battlefield();
    void AddCard(card& newCard, bool support=true, int slot=-1);
    void RemoveCard(int slot, bool support=true);
    list<const card*> getCards() const;

    private:
    typedef struct {int index; card* _card;} cardIndex;
    const vector<sf::Vector2f> battlePositionsOffset  = {{-50,-50}, { 50,-50}};
    const vector<sf::Vector2f> supportPositionsOffset = {{-75, 50}, {-25, 50}, {25,50}, {75,50}}; 
    vector<cardIndex> supportCards;
    vector<cardIndex> battleCards;
    const int MAX_SUPPORT_CARDS = 4;
    const int MAX_BATTLE_CARDS = 2;
    int getNextFreeSlot(vector<cardIndex>& cards, int max);
    card* getCardAt(int slot, int& inIndex, bool support=true);
};