#pragma once

#include <SFML/Graphics.hpp>
#include "ui/UIElement.h"
#include "ui/CardUI.h"

class Card;

using std::shared_ptr;

class Hand : public UIElement{
    public:
    Hand(UISystem* ui):UIElement(ui){name = "Hand";}
    private:
    const float handwidth = 200;
    const float leftmostRotation = -30;
    const int maxHandsize = 10;
    list<shared_ptr<Card>> handCardData = {};
    list<shared_ptr<CardUI>> handCards = {};
    const sf::Vector2f handOffset = {0,-50};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
   
    public:
    void updateHandPositions();
    const list<Card*> getHandData() const;
    bool addCardToHand(shared_ptr<Card> cardtoadd);
    std::shared_ptr<Card> removeCard(Card *cardToRemove);
    void setPosition(const sf::Vector2f &newPos) override {UIElement::setPosition(newPos); updateHandPositions();};
};