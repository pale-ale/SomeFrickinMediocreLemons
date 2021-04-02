#include "Vinesnatcher.h"
#include "../Game.h"
#include "../ui/CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : card::card(ui, pathToImage, description, cost)
{
    setupButtonBinding();
    cardButton->setName("vinesnatcher-button");
    multiSelector = std::make_shared<MultiSelect>(ui);
}

void Vinesnatcher::play(){
    card::play();
}

void Vinesnatcher::onCardDeath(){
    card::onCardDeath();
    if (cardLocation == ECardLocation::battlefieldBattle || 
        cardLocation == ECardLocation::battlefieldBattort || 
        cardLocation == ECardLocation::battlefieldSupport){
        owner->battlefield->removeCard(this);
    }
}

void Vinesnatcher::onCardBeginMouseover(){
    card::onCardBeginMouseover();
}

void Vinesnatcher::tap(){
    card::tap();
    multiSelector->setPosition(getPosition() + sf::Vector2f{-40, 0});
    if (cardLocation == battlefieldBattle){
        multiSelector->addOption(
            {"Attack", std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::attackOptionCallback)});
        return;
    }
    if (cardLocation == battlefieldBattort || cardLocation == battlefieldSupport)
    multiSelector->addOption(
        {"Tap", std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::tapOptionCallback)});
}

void Vinesnatcher::onReceiveSelection(list<card*> cards){
    cout << "Vinesnatcher: " << name << " received selection\n";
    auto card = *cards.begin();
    cout << "Vinesnatcher: " << name << " deals 2 damage to " << card->getName() << ".\n";
    card->takeDamage(2);
}

void Vinesnatcher::tapOptionCallback(){
    owner->awaitingSelection = this;
    CardSelectionInfo csi;
    cout << "Vinesnatcher: " << name << " requesting selection.\n";
    owner->startSelection(csi);
    multiSelector->clear();
    cout << "Vinesnatcher: " << name << " tapped.\n";
}

void Vinesnatcher::attackOptionCallback(){
    cout << "Vinesnatcher attacks!\n";
}