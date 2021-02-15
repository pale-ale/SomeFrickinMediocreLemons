#include "Kalle.h"

Kalle::Kalle() : card::card(pathToImage, description, cost)
{
    setupButtonBinding();
}

void Kalle::play(){
    card::play();
    owner->setLifePoints(owner->getLifePoints()+2000);
    cout << owner->getName() << " has " << owner->getLifePoints() << " HP.\n";
}

void OnCardBeginMouseover(){
    cout << "Unnormaler Doppelklang, alla!\n";
}
