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

void Vinesnatcher::onCardDeath(){
    card::onCardDeath();
    if (cardLocation == ECardLocation::battlefield){
        owner->battlefield->removeCard(this);
    }
}

void Vinesnatcher::onCardBeginMouseover(){
    card::onCardBeginMouseover();
}

void Vinesnatcher::tap(){
    card::tap();
    owner->awaitingSelection = this;
    CardSelectionInfo csi;
    cout << "Vinesnatcher: " << name << " requesting selection.\n";
    owner->startSelection(csi);
    cout << "Vinesnatcher: " << name << " tapped.\n";
}

void Vinesnatcher::onReceiveSelection(list<card*> cards){
    cout << "Vinesnatcher: " << name << " received selection\n";
    auto card = *cards.begin();
    cout << "Vinesnatcher: " << name << " deals 2 damage to " << card->getName() << ".\n";
    card->takeDamage(2);
}