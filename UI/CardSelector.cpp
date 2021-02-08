#include "CardSelector.h"

CardSelector::CardSelector(){}

void CardSelector::setSelectionTarget(const list<card*> cardsToSelectFrom, bool reposition){
    int slotNumberX = 0;
    int slotNumberY = 0;
    int posX = 0;
    int posY = 0;

    auto start = cardsToSelectFrom.begin();
    while (start != cardsToSelectFrom.end()){
        posX = slotNumberX*slotWidth + slotNumberX*slotPaddingX + slotPaddingX;
        posY = slotNumberY*slotHeight + slotNumberY*slotPaddingY + slotPaddingY;
        std::unique_ptr<Button> b;
        if (reposition){
            b = std::make_unique<Button>({posX, posY, slotHeight, slotHeight}, sf::Color{100,100,100,100});
        }
            
        b->setPosition({posX, posY});
        
        
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