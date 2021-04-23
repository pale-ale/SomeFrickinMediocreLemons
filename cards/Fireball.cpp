#include "Fireball.h"

#include "../actions/FireballPlay.h"

Fireball::Fireball(UISystem* ui) : Card::Card(ui, pathToImage, description, "Fireball", cost)
{
    setupActions();
}

void Fireball::setupActions(){
    actions.push_back(std::make_shared<FireballPlay>(owner, this));
}

void Fireball::play(){
    actions[0]->triggerAction();        
}
