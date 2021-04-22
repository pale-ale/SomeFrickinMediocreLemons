#include "Fireball.h"

#include "../Game.h"
#include "../Player.h"

#include "../actions/FireballTap.h"
#include "../events/EventCallback.h"
#include "../ui/Button.h"

Fireball::Fireball(UISystem* ui) : Card::Card(ui, pathToImage, description, "Fireball", cost)
{
    setupButtonBinding();
}

void Fireball::onCardClicked(){
    if (owner->bIsMyTurn && cardLocation == hand){
        cout << "Would now ask for a selection of a playerCard.\n";
    }
}

void Fireball::setupButtonBinding(){
    cardButton->onMouseDownCallback = std::make_shared<EventCallback<Card>>(this, &Fireball::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Fireball>>(this, &Fireball::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardEndMouseover);
}