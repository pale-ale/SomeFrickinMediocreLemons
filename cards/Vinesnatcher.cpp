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
