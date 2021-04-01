#include "Vinesnatcher.h"
#include "../Game.h"
#include "../ui/CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : card::card(ui, pathToImage, description, cost)
{
    setupButtonBinding();
    cardButton->setName("vinesnatcher-button");
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
    multiSelector = std::make_shared<MultiSelect>(ui);
    multiSelector->setPosition(getPosition() + sf::Vector2f{-40, 0});
    multiSelector->addOption(
        {"Tap", std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::tapOptionCallback)});
    multiSelector->addOption(
        {"Attack", std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::attackOptionCallback)});
    addChild(multiSelector);
    return;
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