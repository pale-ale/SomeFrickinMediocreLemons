#include "Card.h"
#include <cmath>
#include "Hand.h"

void Hand::updateHandPositions()
{
    auto start = handCards.begin();
    auto end = handCards.end();
    //calculated for space per card
    float slotWidth = handwidth / handCards.size();
    int currentSlotNumber = 0;
    int xPos = transform.getPosition().x;
    int yPos = transform.getPosition().y;
    int leftHandBoundary = xPos + handOffset.x - handwidth / 2;
    float rotationStep = handCards.size() ? abs(leftmostRotation) / handCards.size() : 0;
    while (start != end)
    {
        float x = slotWidth*currentSlotNumber + 0.5*slotWidth - slotWidth*(handCards.size() / 2.0f);
        float y = -0.003 * pow((x), 2) + 20;
        auto card = (*start);
        auto standardPos = sf::Vector2f(handOffset.x + x, handOffset.y - y);
        card->setPosition(transform.getTransform().transformPoint(standardPos));
        card->setRotation(rotationStep * (currentSlotNumber - (float)handCards.size() / 2) + rotationStep/2 + 
                              transform.getRotation());
        start++;
        currentSlotNumber++;
    }
}
const list<Card*> Hand::getHandData() const
{
    list<Card*> l;
    for (auto c : handCardData){
        l.push_back(c.get());
    }
    return l;
}

bool Hand::addCardToHand(shared_ptr<Card> cardToAdd)
{
    if (handCardData.size() < maxHandsize)
    {
        handCardData.push_back(cardToAdd);
        auto newCardUI = cardToAdd->getCardUI();
        newCardUI->initializeSubComponents();
        handCards.push_back(newCardUI);
        cardToAdd->setFlipState(true);
        cardToAdd->cardLocation = ECardLocation::hand;
        return true;
    }
    return false;
}

std::shared_ptr<Card> Hand::removeCard(Card *cardToRemove)
{
    for (auto cardSharedPtr : handCardData){
        if (cardSharedPtr.get() == cardToRemove){
            handCardData.remove(cardSharedPtr);
            handCards.remove(cardSharedPtr->getCardUI());
            cardToRemove->getCardUI()->reparent(nullptr);
            return cardSharedPtr;
        }
    }
    cout << "Hand: Trying to remove a card that is not in this handCards!\n";
    throw;
}

void Hand::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& card : handCards){
        target.draw(*card);
    }
}