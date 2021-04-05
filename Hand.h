#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"

class Hand : public UIElement{
    public:
    Hand(UISystem* ui):UIElement(ui){name = "Hand";}
    private:
    const float handwidth = 200;
    const float leftmostRotation = -30;
    const int maxHandsize = 10;
    list<shared_ptr<Card>> hand = {};
    const sf::Vector2f handOffset = {0,-50};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (auto& card : hand){
            target.draw(*card);
        }
    }

    public:
    void updateHandPositions();
    const list<Card*> getHand() const;
    bool addCardToHand(shared_ptr<Card> cardtoadd);
    std::shared_ptr<Card> removeCard(Card *cardToRemove);
    void setPosition(const sf::Vector2f &newPos) override {UIElement::setPosition(newPos); updateHandPositions();};
};