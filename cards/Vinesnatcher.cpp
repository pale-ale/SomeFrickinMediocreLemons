#include "Vinesnatcher.h"
#include "../Game.h"
#include "CardSelector.h"
#include "../Battlefield.h"

Vinesnatcher::Vinesnatcher() : card::card(pathToImage, description, cost)
{
    SetupButtonBinding();
}

void Vinesnatcher::Play(){
    card::Play();
    auto g = owner->getGame();
    list<const card*> opponentCards;
    for (auto p : g->players){
        if(p == owner){
            continue;
        }
        opponentCards = p->battlefield.getCards();
    }
    owner->cardSelector.setSelectionTarget(opponentCards, true);
}
