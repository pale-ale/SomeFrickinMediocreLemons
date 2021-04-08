#include "Vinesnatcher.h"
#include "../Game.h"
#include "../ui/CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : Card::Card(ui, pathToImage, description, "Vinesnatcher", cost)
{
    setupButtonBinding();
    cardButton->setName("vinesnatcher-button");
    multiSelector = std::make_shared<MultiSelect>(ui);
    multiSelector->reparent(this);
    multiSelector->setPosition(getPosition() + sf::Vector2f{-40, 0});
    addChild(multiSelector);
    setupActions();
}

void Vinesnatcher::onCardDeath(){
    Card::onCardDeath();
    if (cardLocation == ECardLocation::battlefieldBattle || 
        cardLocation == ECardLocation::battlefieldBattort || 
        cardLocation == ECardLocation::battlefieldSupport){
        owner->battlefield->removeCard(this);
    }
}
