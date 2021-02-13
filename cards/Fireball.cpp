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
            p->setLifePoints(p->getLifePoints()-100);
            cout << p->getName() << " has " << p->getLifePoints() << " HP.\n";
        }
    }
}

void Fireball::OnCardBeginMouseover(){
    cout << "*sizzle*\n";  
}