#include "Hand.h"
#include <cmath>

void Hand::updateHandPositions()
{
    auto start = hand.begin();
    auto end = hand.end();
    //calculated for space per card
    float slotWidth = handwidth / hand.size();
    int currentSlotNumber = 0;
    int xPos = transform.getPosition().x;
    int yPos = transform.getPosition().y;
    int leftHandBoundary = xPos + handOffset.x - handwidth / 2;
    float rotationStep = abs(leftmostRotation) / hand.size();
    while (start != end)
    {
        float x = slotWidth*currentSlotNumber + 0.5*slotWidth - slotWidth*(hand.size() / 2.0f);
        float y = -0.003 * pow((x), 2) + 20;
        auto card = (*start);
        auto standardPos = sf::Vector2f(handOffset.x + x, handOffset.y - y);
        card->setPosition(transform.getTransform().transformPoint(standardPos));
        card->setRotation(rotationStep * (currentSlotNumber - (float)hand.size() / 2) + rotationStep/2 + 
                              transform.getRotation());
        start++;
        currentSlotNumber++;
    }
}
const list<shared_ptr<card>> Hand::getHand() const
{
    return hand;
}

bool Hand::addCardToHand(shared_ptr<card>& cardtoadd)
{
    if (hand.size() < maxHandsize)
    {
        hand.push_back(cardtoadd);
        cardtoadd->attachTo(this);
        return true;
    }
    return false;
}

shared_ptr<card> Hand::removeCard(card* cardToRemove)
{
    auto card = find_if(hand.begin(), hand.end(), 
        [cardToRemove] (const auto& s) { 
            return s.get() == cardToRemove; 
        } );

    if (card != hand.end()){
        hand.erase(card);
        removeChild(card->get());
        return *card;
    }
    cout << "trying to remove a card that doesnt exist\n";
    return nullptr;
}
