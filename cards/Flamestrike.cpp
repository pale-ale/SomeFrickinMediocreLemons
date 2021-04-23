#include "Flamestrike.h"

#include "../actions/FlamestrikePlay.h"

Flamestrike::Flamestrike(UISystem* ui) : Card::Card(ui, pathToImage, description, "Flamestrike", cost)
{
    setupActions();
}

void Flamestrike::setupActions(){
    actions.push_back(std::make_shared<FlamestrikePlay>(owner, this));
}

void Flamestrike::play(){
    actions[0]->triggerAction();        
}
