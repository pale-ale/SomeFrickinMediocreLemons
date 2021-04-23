#include "Fireball.h"

#include "../actions/FireballTap.h"

Fireball::Fireball(UISystem* ui) : Card::Card(ui, pathToImage, description, "Fireball", cost)
{
    setupActions();
}

void Fireball::setupActions(){
    actions.push_back(std::make_shared<FireballTap>(owner, this));
}

void Fireball::play(){
    actions[0]->triggerAction();        
}
