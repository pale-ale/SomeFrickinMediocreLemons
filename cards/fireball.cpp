#include "fireball.h"
#include "../Game.h"

Fireball::Fireball() : card::card()
{
    pathToImage = "/usr/share/test/resources/Fireball.png";
    description="A fireball that\nattacks enemies";
    updateCardImage();
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
