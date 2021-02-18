#pragma once

#include "UISystem.h"
#include "../card.h"

class CardSelector : public UIElement{
    public:
    CardSelector(UISystem* ui);
    void setSelectionTarget(const list<shared_ptr<const card>> &cardsToSelectFrom, bool displayAsList);
    list<shared_ptr<const card>> getSelectedCards() const;
    void resetSelection(){selectedCards.clear();}
    bool bIsCurrentlySelecting = false;
    
    const int gridWidth = 8;
    const int slotPaddingX = 5;
    const int slotPaddingY = 10;
    const float slotWidth = 50;
    const float slotHeight = 75;

    private:
    list<shared_ptr<Button>> buttons;
    list<shared_ptr<const card>> selectedCards;
    list<shared_ptr<const card>> cards;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        for (auto& b : buttons){
            target.draw(*(b.get()));
        }
    }
    void selectedCardClickCallback();
};