#include "Fireball.h"
#include "../Game.h"

Fireball::Fireball(UISystem* ui) : card::card(ui, pathToImage, description, cost)
{
    setupButtonBinding();
}

void Fireball::play(){
    card::play();
    auto g = owner->getGame();
    for (auto* p : g->players){
        if (p != owner){
            p->setLifePoints(p->getLifePoints()-100);
            cout << p->getName() << " has " << p->getLifePoints() << " HP.\n";
        }
    }
}

void Fireball::onCardBeginMouseover(){
    cout << "*sizzle*\n";  
}