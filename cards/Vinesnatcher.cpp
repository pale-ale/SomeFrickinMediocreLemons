#include "Vinesnatcher.h"

#include "../Battlefield.h"
#include "../CardSelectionInfo.h"
#include "../Game.h"

#include "../actions/DefaultAttack.h"
#include "../actions/VinesnatcherTap.h"

#include "../events/EventCallback.h"

#include "../ui/Button.h"
#include "../ui/CardSelector.h"

Vinesnatcher::Vinesnatcher(UISystem* ui) : Card::Card(ui, pathToImage, description, "Vinesnatcher", cost)
{
    setupButtonBinding();
    cardButton->setName("vinesnatcher-button");
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

void Vinesnatcher::setupButtonBinding(){
    cardButton->onClickCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardEndMouseover);
    cardButton->onDragMoveCallback = std::make_shared<EventCallback<Card, const sf::Vector2f&>>(this, &Card::OnDragMove);
    cardButton->onDragEndCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragEnd);
    cardButton->onDragStartCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragStart);
}