#pragma once
#include <SFML/Graphics.hpp>
#include "card.h"

class Hand : public UIElement{
    private:
    const float handwidth = 200;
    const float leftmostRotation = -30;
    const int maxHandsize = 10;
    list<card*> hand = {};
    const sf::Vector2f handOffset = {0,-50};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (card* card : hand){
            target.draw(*card);
        }
    }

    public:
    void updateHandPositions();
    const list<card*>* getHand() const;
    bool addCardToHand(card * cardtoadd);
    bool insertHand(list<card*>::iterator it);
    bool removeCard(card* cardtoremove);
};