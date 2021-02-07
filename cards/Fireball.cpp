#include "Fireball.h"
#include "../Game.h"

Fireball::Fireball() : card::card(pathToImage, description, cost)
{
    SetupButtonBinding();
}

void Fireball::Play(){
    card::Play();
    auto g = owner->getGame();
    for (auto* p : g->players){
        if (p != owner){
            p->LifePoints -= 100;
            cout << p->getName() << " has " << p->LifePoints << " HP.\n";
        }
    }
}
