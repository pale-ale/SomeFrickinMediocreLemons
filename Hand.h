#pragma once
#include <SFML/Graphics.hpp>
#include "card.h"

class Hand : public UIElement{
    public:
    Hand(UISystem* ui):UIElement(ui){}
    private:
    const float handwidth = 200;
    const float leftmostRotation = -30;
    const int maxHandsize = 10;
    list<shared_ptr<card>> hand = {};
    const sf::Vector2f handOffset = {0,-50};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& card : hand){
            target.draw(*card);
        }
    }

    public:
    void updateHandPositions();
    const list<shared_ptr<card>>& getHand() const;
    bool addCardToHand(shared_ptr<card>& cardtoadd);
    shared_ptr<card> removeCard(card* cardtoremove);
    void setPosition(sf::Vector2f newPos) override {UIElement::setPosition(newPos); updateHandPositions();};
};