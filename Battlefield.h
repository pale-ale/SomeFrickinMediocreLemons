#pragma once

#include <algorithm>
#include <iostream>
#include "card.h"
#include "Placeable.h"

class Battlefield : public Placeable{
    public:
    Battlefield(UISystem* ui);
    void addCard(shared_ptr<card> newCard, bool support=true, int slot=-1);
    void removeCard(int slot, bool support=true);
    void removeCard(card *card);
    list<card*> getCards() const;
    void printCards();

    private:
    struct cardIndex{
        int index; 
        shared_ptr<card> _card;
        bool operator==(cardIndex other){
            return _card == other._card;
        }
    };
    const vector<sf::Vector2f> battlePositionsOffset  = {{-50,-50}, { 50,-50}};
    const vector<sf::Vector2f> supportPositionsOffset = {{-75, 50}, {-25, 50}, {25,50}, {75,50}}; 
    list<cardIndex> supportCards;
    list<cardIndex> battleCards;
    const int MAX_SUPPORT_CARDS = 4;
    const int MAX_BATTLE_CARDS = 2;
    int getNextFreeSlot(list<cardIndex> &cards, int max);
    card *getCardAt(int slot, bool support=true);
};