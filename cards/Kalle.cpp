#include "Kalle.h"

Kalle::Kalle(UISystem* ui) : Card::Card(ui, pathToImage, description, cost)
{
    setupButtonBinding();
}

void Kalle::play(){
    Card::play();
    owner->setLifePoints(owner->getLifePoints()+2000);
    cout << owner->getName() << " has " << owner->getLifePoints() << " HP.\n";
}

void OnCardBeginMouseover(){
    cout << "Unnormaler Doppelklang, alla!\n";
}
