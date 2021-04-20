#include "Fireball.h"

#include "../Game.h"
#include "../Player.h"

#include "../events/EventCallback.h"

#include "../ui/Button.h"

Fireball::Fireball(UISystem* ui) : Card::Card(ui, pathToImage, description, "Fireball", cost)
{
    setupButtonBinding();
}

void Fireball::play(){
    Card::play();
    auto g = owner->getGame();
    for (auto* p : g->players){
        if (p != owner){
            p->setLifePoints(p->getLifePoints()-100);
            cout << p->getName() << " has " << p->getLifePoints() << " HP.\n";
        }
    }
}

void Fireball::onCardBeginMouseover(){
    cout << "*sizzle*\n";  
}

void Fireball::setupButtonBinding(){
    cardButton->onMouseDownCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Fireball>>(this, &Fireball::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardEndMouseover);
}