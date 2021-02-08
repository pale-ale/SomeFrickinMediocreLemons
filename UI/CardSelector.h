#pragma once

#include "UISystem.h"
#include "../card.h"

class CardSelector : public UIElement{
    public:
    CardSelector();
    void setSelectionTarget(const list<const card*> &cardsToSelectFrom, bool reposition);
    list<card*> getSelectedCards() const;
    bool bIsCurrentlySelecting;
    
    const int gridWidth = 8;
    const int slotPaddingX = 5;
    const int slotPaddingY = 10;
    const float slotWidth = 50;
    const float slotHeight = 75;

    private:
    list<std::shared_ptr<Button>> buttons;
    list<card*> selectedCards;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        for (auto& b : buttons){
            target.draw(*(b.get()));
        }
    }
};