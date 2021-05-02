#include "CardSelector.h"
#include "../Player.h"
#include "../events/EventCallback.h"
#include "CardUI.h"

CardSelector::CardSelector(UISystem *ui) : UIElement(ui)
{
    name = "CardSelector";
}

void CardSelector::setSelectionTarget(const list<Card*> &cardsToSelectFrom, bool reposition, CardSelectionInfo csi)
{
    cards = cardsToSelectFrom;
    cardSelectionInfo = csi;
    int slotNumberX = 0;
    int slotNumberY = 0;
    float posX = 0;
    float posY = 0;
    buttons.erase(buttons.begin(), buttons.end());
    vector<sf::Vector2f> corners = {
        {-slotWidth * .5f, -slotHeight * .5f},
        {-slotWidth * .5f, slotHeight * .5f},
        {slotWidth * .5f, slotHeight * .5f},
        {slotWidth * .5f, -slotHeight * .5f}
    };

    for (auto &c : cards)
    {
        auto cUI = c->getCardUI();
        auto button = std::make_shared<Button>(ui, sf::Color{50, 50, 255, 100}, sf::Color{50, 50, 200, 100}, corners);
        if (reposition)
        {
            //WIP
            posX = slotNumberX * slotWidth + slotNumberX * slotPaddingX + slotPaddingX + slotWidth / 2;
            posY = slotNumberY * slotHeight + slotNumberY * slotPaddingY + slotPaddingY + slotHeight / 2;
            button->setPosition({posX, posY});
            slotNumberX += 1;
            if (slotNumberX >= gridWidth)
            {
                slotNumberX = 0;
                slotNumberY++;
            }
        }
        else
        {
            button->setPosition({posX, posY});
            button->initializeSubComponents();
            button->setName("cardSelectorButton");
            cout << "added button as listener.\n";
            button->setRotation(cUI->getRotation());
            button->setPosition(cUI->getPosition());
        }
        button->onMouseDownCallback = std::make_shared<EventCallback<CardSelector>>(this, &CardSelector::selectedCardClickCallback);
        buttons.push_back(std::move(button));
    }
}

list<Card *> CardSelector::getSelectedCards() const
{
    return selectedCards;
}

void CardSelector::selectedCardClickCallback()
{
    auto cardStart = cards.begin();

    for (auto &b : buttons)
    {
        if (b->isPressed)
        {
            //code is run when an eligible card is clicked
            buttons.remove(b);
            selectedCards.push_back(*cardStart);
            if (selectedCards.size() == cardSelectionInfo.maxCompleteSelectionCount)
            {
                Player *p = static_cast<Player *>(parent);
                if (p)
                {
                    p->cardSelectionUpdated();
                }
                else
                {
                    cout << "A cardselector must have a player as a parent.\n";
                    throw;
                }
                return;
            }
        }
        cardStart++;
    }
}