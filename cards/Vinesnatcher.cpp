#include "Vinesnatcher.h"
#include "../Game.h"
#include "CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : card::card(ui, pathToImage, description, cost)
{
    setupButtonBinding();
}

void Vinesnatcher::play(){
    card::play();
}

void Vinesnatcher::onCardBeginMouseover(){
    card::onCardBeginMouseover();
}

void Vinesnatcher::tap(){
    auto ownerSelection = owner->cardSelector.getSelectedCards();
    
    if (ownerSelection.size() == 0){
        owner->startSelection();
        owner->awaitingSelection = this;
        return;
    }
    
    if (ownerSelection.size() == 1 && owner->awaitingSelection == this){
        owner->cardSelector.resetSelection();
        cout << "vinesnatcher tapped.\n";
        owner->awaitingSelection = nullptr;
        auto& card = *(ownerSelection.begin());
        cout << card->getName() << "Vinesnatcher deals 2 damage to " << card->getName() << ".";
        card->takeDamage(2);
    }
}