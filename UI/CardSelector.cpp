#include "CardSelector.h"
#include "../Player.h"

CardSelector::CardSelector(UISystem *ui) : UIElement(ui)
{
}

void CardSelector::setSelectionTarget(const list<shared_ptr<const card>> &cardsToSelectFrom, bool reposition)
{
    cards = cardsToSelectFrom;
    int slotNumberX = 0;
    int slotNumberY = 0;
    float posX = 0;
    float posY = 0;
    buttons.erase(buttons.begin(), buttons.end());

    for (const shared_ptr<const card>& c : cardsToSelectFrom)
    {
        shared_ptr<Button> b;
        if (reposition)
        {
            //WIP
            posX = slotNumberX * slotWidth + slotNumberX * slotPaddingX + slotPaddingX + slotWidth / 2;
            posY = slotNumberY * slotHeight + slotNumberY * slotPaddingY + slotPaddingY + slotHeight / 2;
            b = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
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
            b = std::make_unique<Button>(ui, sf::FloatRect{posX, posY, slotWidth, slotHeight},
                                         sf::Color{0, 255, 255, 150});
            b->setRotation(c->getRotation());
            b->setPosition(c->getPosition());
        }
        b->onMouseDownCallback = new EventCallback<CardSelector>(this, &CardSelector::selectedCardClickCallback);
        buttons.push_back(b);
    }
}

list<shared_ptr<const card>> CardSelector::getSelectedCards() const
{
    return selectedCards;
}

void CardSelector::selectedCardClickCallback()
{
    auto cardStart = cards.begin();
   
    for (auto& b : buttons){
        if (b->isPressed){
            cout << "selector use count: " << (*cardStart).use_count() << endl;
            selectedCards.push_back(*cardStart);
            buttons.remove(b);
            ui->removeListener(b.get());
            Player* p = dynamic_cast<Player*>(parent);
            if (p){
                p->cardSelectionUpdated();
            }
            return;
        }
        cardStart++;
    }
}