#include "CardSelector.h"
#include "../Player.h"

CardSelector::CardSelector(UISystem *ui) : UIElement(ui)
{
}

void CardSelector::setSelectionTarget(const list<card*> &cardsToSelectFrom, bool reposition, CardSelectionInfo csi)
{
    cards = cardsToSelectFrom;
    cardSelectionInfo = csi;
    int slotNumberX = 0;
    int slotNumberY = 0;
    float posX = 0;
    float posY = 0;
    buttons.erase(buttons.begin(), buttons.end());

    for (auto &c : cards)
    {
        unique_ptr<Button> button;
        if (reposition)
        {
            //WIP
            posX = slotNumberX * slotWidth + slotNumberX * slotPaddingX + slotPaddingX + slotWidth / 2;
            posY = slotNumberY * slotHeight + slotNumberY * slotPaddingY + slotPaddingY + slotHeight / 2;
            button = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
                                         sf::Color{255, 255, 255, 255});
            slotNumberX += 1;
            if (slotNumberX >= gridWidth)
            {
                slotNumberX = 0;
                slotNumberY++;
            }
        }
        else
        {
            button = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
                                         sf::Color{0, 255, 255, 150});
            cout << "added button as listener.\n";
            button->setRotation(c->getRotation());
            button->setPosition(c->getPosition());
        }
        button->onMouseDownCallback = std::make_shared<EventCallback<CardSelector>>(this, &CardSelector::selectedCardClickCallback);
        buttons.push_back(std::move(button));
    }
}

list<card*> CardSelector::getSelectedCards() const
{
    return selectedCards;
}

void CardSelector::selectedCardClickCallback()
{
    auto cardStart = cards.begin();

    for (auto& b : buttons){
        if (b->isPressed){
            //code is run when an eligible card is clicked
            buttons.remove(b);
            selectedCards.push_back(*cardStart);
            if (selectedCards.size() == cardSelectionInfo.maxCompleteSelectionCount){
                Player* p = static_cast<Player*>(parent);
                if (p){
                    p->cardSelectionUpdated();
                }else{
                    cout << "A cardselector must have a player as a parent.\n";
                    throw;
                }
                return;
            }
        }
        cardStart++;
    }
}