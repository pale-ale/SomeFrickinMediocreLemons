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
    owner->awaitingSelection = this;
    CardSelectionInfo csi;
    cout << name << " requesting selection.\n";
    owner->startSelection(csi);
    cout << name << " tapped.\n";
}

void Vinesnatcher::onReceiveSelection(list<shared_ptr<card>> cards){
    auto card = *cards.begin();
    cout << "Vinesnatcher deals 2 damage to " << card->getName() << ".\n";
    card->takeDamage(2);
}