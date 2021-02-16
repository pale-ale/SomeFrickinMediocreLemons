#include "CardSelector.h"

CardSelector::CardSelector(UISystem* ui):
UIElement(ui)
{}

void CardSelector::setSelectionTarget(const list<const card *> &cardsToSelectFrom, bool reposition)
{
    int slotNumberX = 0;
    int slotNumberY = 0;
    float posX = 0;
    float posY = 0;
    buttons.erase(buttons.begin(), buttons.end());

    for (const card *c : cardsToSelectFrom)
    {
        std::shared_ptr<Button> b;
        if (reposition)
        {
            //WIP
            posX = slotNumberX * slotWidth + slotNumberX * slotPaddingX + slotPaddingX + slotWidth / 2;
            posY = slotNumberY * slotHeight + slotNumberY * slotPaddingY + slotPaddingY + slotHeight / 2;
            b = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
                                         sf::Color{255,255,255,255});
            slotNumberX += 1;
            if (slotNumberX >= gridWidth)
            {
                slotNumberX = 0;
                slotNumberY++;
            }
        }
        else
        {
            b = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
                                         sf::Color{255,255,255,150});
            b->setRotation(c->getRotation());
            b->setPosition(c->getPosition());
        }
        b.get()->onBeginMouseoverCallback = new EventCallback<CardSelector>(this, &CardSelector::selectedCardClickCallback);
        buttons.push_back(b);
        //unfortunately we need to revise the uisystem or registration of listeners thereof. 
        //buttons created here are not managed by the ui, i.e. they will never receive any click, move, etc.-events
    }
}

list<card *> CardSelector::getSelectedCards() const
{
    return selectedCards;
}