#include "FireballTap.h"

FireballTap::FireballTap(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
{
    if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "FireballTapTexture.png"))
    {
        cout << "FireballTap: Error loading image '" 
                << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
    }
}

void FireballTap::triggerAction()
{
    cout << "FireballTap: Clicked\n";
    if (owningPlayer && owningCard)
    {
        owningPlayer->awaitingSelection = this;
        CardSelectionInfo csi;
        csi.canAttackHeroDirectly = true;
        cout << "FireballTap: " << owningCard->getName() << " requesting selection.\n";
        owningPlayer->startSelection(csi);
        cout << "FireballTap: " << owningCard->getName() << " tapped.\n";
        return;
    }
    cout << "FireballTap: OwningCard and OwningPlayer are required.\n";
    throw;
}

void FireballTap::onReceiveSelection(std::list<Card*> cards)
{
    
    auto card = *cards.begin();
    cout << "FireballTap: " << owningCard->getName() << " deals 3 damage to " << card->getName() << ".\n";
    card->takeDamage(2);
}