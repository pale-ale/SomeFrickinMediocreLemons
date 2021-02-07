#include "Kalle.h"

Kalle::Kalle() : card::card(pathToImage, description, cost)
{
    SetupButtonBinding();
}

void Kalle::Play(){
    card::Play();
    owner->LifePoints += 2000;
    cout << owner->getName() << " has " << owner->LifePoints << " HP.\n";
}