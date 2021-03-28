#pragma once

#include <algorithm>
#include <iostream>
#include "Card.h"
#include "Placeable.h"

class Battlefield : public Placeable{
    public:
    Battlefield(UISystem* ui);
    void addCard(shared_ptr<card> newCard, bool support=true, int slot=-1);
    void removeCard(int slot, bool support=true);
    void removeCard(card *card);
    list<card*> getCards() const;
    void setDrawFreeSpaces(bool drawFreeSpaces);
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
    const vector<sf::Vector2f> supportPositionsOffset = {{-78, 50}, {-26, 50}, {26,50}, {78,50}}; 
    list<cardIndex> supportCards;
    list<cardIndex> battleCards;
    list<shared_ptr<Button>> emptySpaceDisplay;
    const int MAX_SUPPORT_CARDS = 4;
    const int MAX_BATTLE_CARDS = 2;
    int getNextFreeSlot(list<cardIndex> &cards, int max);
    card *getCardAt(int slot, bool support=true);

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        Placeable::draw(target, state);
        for (auto x : emptySpaceDisplay){
            target.draw(*x.get());
        }
    }};