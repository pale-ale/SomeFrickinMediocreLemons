#pragma once

#include "UISystem.h"
#include "../Card.h"
#include "../CardSelectionInfo.h"
#include "Button.h"

class CardUI;

template <typename ...T>
class IEventCallback;

class CardSelector : public UIElement{
    public:
    CardSelector(UISystem* ui);
    void setSelectionTarget(const list<Card*> &cardsToSelectFrom, bool displayAsList, CardSelectionInfo csi);
    list<Card*> getSelectedCards() const;
    void resetSelection(){
        cards.clear();
        selectedCards.clear();
        buttons.clear();
        cout << "Cardselector cleared seleciton.\n";
    }
    bool bIsCurrentlySelecting = false;
    CardSelectionInfo cardSelectionInfo;
    
    const int gridWidth = 8;
    const int slotPaddingX = 5;
    const int slotPaddingY = 10;
    const float slotWidth = Settings::cardSize.x * Settings::cardScale.x;
    const float slotHeight = Settings::cardSize.y * Settings::cardScale.y;

    private:
    list<shared_ptr<Button>> buttons;
    list<Card*> selectedCards;
    list<Card*> cards;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        for (auto& b : buttons){
            target.draw(*b);
        }
    }
    void selectedCardClickCallback();
};