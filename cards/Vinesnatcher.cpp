#include "Vinesnatcher.h"
#include "../Game.h"
#include "CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher() : card::card(pathToImage, description, cost)
{
    setupButtonBinding();
}

void Vinesnatcher::play(){
    card::play();
}

void Vinesnatcher::onCardBeginMouseover(){
    card::onCardBeginMouseover();
    cout << "vineover\n";
}
