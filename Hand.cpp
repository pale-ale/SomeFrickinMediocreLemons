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
const list<Card*> Hand::getHand() const
{
    list<Card*> l;
    for (auto c : hand){
        l.push_back(c.get());
    }
    return l;
}

bool Hand::addCardToHand(shared_ptr<Card> cardToAdd)
{
    if (hand.size() < maxHandsize)
    {
        hand.push_back(cardToAdd);
        addChild(cardToAdd);
        cardToAdd->reparent(this);
        cardToAdd->setFlipState(true);
        cardToAdd->cardLocation = ECardLocation::hand;
        return true;
    }
    return false;
}

std::shared_ptr<Card> Hand::removeCard(Card *cardToRemove)
{
    for (auto cardSharedPtr : hand){
        if (cardSharedPtr.get() == cardToRemove){
            hand.remove(cardSharedPtr);
            cardToRemove->reparent(nullptr);
            return cardSharedPtr;
        }
    }
    cout << "Hand: Trying to remove a card that is not in this hand!\n";
    throw;
}
