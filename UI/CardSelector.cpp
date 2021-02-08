#include "CardSelector.h"

CardSelector::CardSelector(){}

void CardSelector::setSelectionTarget(const list<const card*> &cardsToSelectFrom, bool reposition){
    int slotNumberX = 0;
    int slotNumberY = 0;
    float posX = 0;
    float posY = 0;
    buttons.erase(buttons.begin(), buttons.end());

    for (const card* c : cardsToSelectFrom){
        posX = slotNumberX*slotWidth + slotNumberX*slotPaddingX + slotPaddingX + slotWidth/2;
        posY = slotNumberY*slotHeight + slotNumberY*slotPaddingY + slotPaddingY + slotHeight/2;
        std::shared_ptr<Button> b;
        if (reposition){
            b = std::make_unique<Button>(sf::FloatRect{posX, posY, slotWidth, slotHeight}, 
                                         sf::Color{100,100,100,255});
            b->setRotation(c->getRotation());
            b->setPosition({posX, posY});
            cout << "adding button\n";
            buttons.push_back(b);
        }
        slotNumberX += 1;
        if (slotNumberX >= gridWidth){
            slotNumberX = 0;
            slotNumberY++;
        }
    }
}

list<card*> CardSelector::getSelectedCards() const{
    return selectedCards;
}