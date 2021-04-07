#pragma once

#include <algorithm>
#include "Card.h"
#include "ECardLocation.h"
#include "GlobalFunctions.h"
#include <iostream>
#include <math.h>
#include "Placeable.h"

using std::shared_ptr;

class Battlefield : public Placeable{
    public:
    Battlefield(UISystem* ui);
    void addCard(shared_ptr<Card> newCard, bool support=true, int slot=-1);
    void removeCard(int slot, bool support=true);
    void removeCard(Card *card);
    list<Card*> getCards() const;
    void setDrawFreeSpaces(bool drawFreeSpaces, bool support);
    vector<sf::Vector2f> getFreeSnapPoints(bool support);
    void printCards();

    private:
    struct cardIndex{
        int index; 
        shared_ptr<Card> _card;
        bool operator==(cardIndex other){
            return _card == other._card;
        }
    };
    struct positionIndex{
        int index;
        sf::Vector2f pos;
    };
    const vector<positionIndex> battlePositionsOffset = {{0, {-60, 40}}, {1, {60, 40}}};
    const vector<positionIndex> supportPositionsOffset = {{0, {-100, 65}}, {1, {-20, 65}}, {2, {20,65}}, {3, {100,65}}}; 
    list<cardIndex> supportCards;
    list<cardIndex> battleCards;
    list<shared_ptr<sf::RectangleShape>> emptySpaceDisplay;
    const int MAX_SUPPORT_CARDS = 4;
    const int MAX_BATTLE_CARDS = 2;
    int getNextFreeSlot(bool support);
    Card *getCardAt(int slot, bool support=true);
    ECardLocation positionToCardLocation(int index, bool support);

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        Placeable::draw(target, state);
        for (auto x : emptySpaceDisplay){
            target.draw(*x.get());
        }
    }
    sf::Vector2f toGlobal(const sf::Vector2f &inPos){
        return transform.getTransform().transformPoint(inPos);
    }
    vector<int> getFreeIndices(bool support){
        list<cardIndex> cis = support ? supportCards : battleCards;
        vector<int> freeIndices;
        int max = support ? MAX_SUPPORT_CARDS : MAX_BATTLE_CARDS ;
        for (int i=0; i<max; ++i){
            bool stillFree = true;
            for (const auto &ci : cis){
                if (ci.index == i){
                    stillFree = false;
                    break;
                }
            }
            if (stillFree){
                freeIndices.push_back(i);
            }
        }
        return freeIndices;
    }
    };