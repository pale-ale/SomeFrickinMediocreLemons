#include "Kalle.h"

Kalle::Kalle() : card::card(pathToImage, description, cost)
{
    SetupButtonBinding();
}

void Kalle::Play(){
    card::Play();
    owner->setLifePoints(owner->getLifePoints()+2000);
    cout << owner->getName() << " has " << owner->getLifePoints() << " HP.\n";
}