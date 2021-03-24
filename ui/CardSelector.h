#pragma once

#include "UISystem.h"
#include "../Card.h"
#include "../CardSelectionInfo.h"

class CardSelector : public UIElement{
    public:
    CardSelector(UISystem* ui);
    void setSelectionTarget(const list<card*> &cardsToSelectFrom, bool displayAsList, CardSelectionInfo csi);
    list<card*> getSelectedCards() const;
    void resetSelection(){
        cards.clear();
        selectedCards.clear();
        cout << "Cardselector cleared seleciton.\n";
    }
    bool bIsCurrentlySelecting = false;
    CardSelectionInfo cardSelectionInfo;
    
    const int gridWidth = 8;
    const int slotPaddingX = 5;
    const int slotPaddingY = 10;
    const float slotWidth = 50;
    const float slotHeight = 75;

    private:
    list<unique_ptr<Button>> buttons;
    list<card*> selectedCards;
    list<card*> cards;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        for (auto& b : buttons){
            target.draw(*(b.get()));
        }
    }
    void selectedCardClickCallback();
};