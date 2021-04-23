#include "CardManagement.h"

#include "cards/Fireball.h"
#include "cards/Flamestrike.h"
#include "cards/Kalle.h"
#include "cards/Vinesnatcher.h"



std::shared_ptr<Card> CardSpawner::SpawnCard(UISystem *ui, CardTypes::Cards card){
    switch (card)
    {
    case CardTypes::Cards::Fireball:
        return std::make_shared<Fireball>(ui);
    case CardTypes::Cards::Flamestrike:
        return std::make_shared<Flamestrike>(ui);
    case CardTypes::Cards::Vinesnatcher:
        return std::make_shared<Vinesnatcher>(ui);
    
    default:
        return nullptr;
    }
}

std::shared_ptr<Card> CardSpawner::SpawnCardRandom(UISystem *ui){
    int e = rand() % CardTypes::Cards::MAX;
    return SpawnCard(ui, static_cast<CardTypes::Cards>(e));
}

