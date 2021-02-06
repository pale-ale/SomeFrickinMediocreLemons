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
        auto standardPos = sf::Vector2f(handOffset.x + x, handOffset.y - y);
        (*start)->setPosition(transform.getTransform().transformPoint(standardPos));
        (*start)->setRotation(rotationStep * (currentSlotNumber - (float)hand.size() / 2) + rotationStep/2 + 
                              transform.getRotation());
        start++;
        currentSlotNumber++;
    }
}
const list<card *> *Hand::getHand() const
{
    return &hand;
}

bool Hand::addCardToHand(card *cardtoadd)
{
    if (hand.size() < maxHandsize)
    {
        hand.push_back(cardtoadd);
        cardtoadd->attachTo(this);
        return true;
    }
    return false;
}

bool Hand::removeCard(card *cardtoremove)
{
    list<card *>::iterator playedCard = find(hand.begin(), hand.end(), cardtoremove);
    if (*playedCard){
        hand.erase(playedCard);
        removeChild(*playedCard);
        return true;
    }
    else{
        cout << "trying to remove a card that doesnt exist\n";
        return false;
    }
}
