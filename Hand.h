#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"

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
    const list<card*> getHand() const;
    bool addCardToHand(shared_ptr<card> cardtoadd);
    std::shared_ptr<card> removeCard(card *cardToRemove);
    void setPosition(const sf::Vector2f &newPos) override {UIElement::setPosition(newPos); updateHandPositions();};
};