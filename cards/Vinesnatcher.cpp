#include "Vinesnatcher.h"

#include "../Battlefield.h"
#include "../CardSelectionInfo.h"

#include "../ui/Button.h"

#include "../actions/DefaultAttack.h"
#include "../actions/VinesnatcherTap.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : Card::Card(ui, pathToImage, description, "Vinesnatcher", cost)
{
    //cardButton->setName("vinesnatcher-button");
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

void Vinesnatcher::setupActions(){
    actions.push_back(make_shared<DefaultAttack>(owner, this));
    actions.push_back(make_shared<VinesnatcherTap>(owner, this));
}
