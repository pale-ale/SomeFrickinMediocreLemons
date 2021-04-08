#include "Fireball.h"
#include "../Game.h"

Fireball::Fireball(UISystem* ui) : Card::Card(ui, pathToImage, description, "Fireball", cost)
{
    setupButtonBinding();
}

void Fireball::play(){
    Card::play();
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