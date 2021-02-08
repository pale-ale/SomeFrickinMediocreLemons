#pragma once

#include "UISystem.h"
#include "../card.h"

class CardSelector : public UIElement{
    public:
    CardSelector();
    void setSelectionTarget(const list<card*> cardsToSelectFrom, bool reposition);
    list<card*> getSelectedCards() const;
    bool bIsCurrentlySelecting;
    
    const int gridWidth = 8;
    const int slotPaddingX = 10;
    const int slotPaddingY = 10;
    const int slotWidth = 40;
    const int slotHeight = 75;

    private:
    list<std::unique_ptr<Button>> buttons;
    list<card*> selectedCards;
};