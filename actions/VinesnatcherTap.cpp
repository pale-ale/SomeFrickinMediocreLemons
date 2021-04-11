#include "VinesnatcherTap.h"

VinesnatcherTap::VinesnatcherTap(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
{
    if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "VinesnatcherTapTexture.png"))
    {
        cout << "VinesnatcherTap: Error loading image '" 
                << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
    }
}

void VinesnatcherTap::triggerAction()
{
    cout << "VinesnatcherAction: Clicked\n";
    if (owningPlayer && owningCard)
    {
        owningPlayer->awaitingSelection = this;
        CardSelectionInfo csi;
        cout << "VinesnatcherAction: " << owningCard->getName() << " requesting selection.\n";
        owningPlayer->startSelection(csi);
        cout << "VinesnatcherAction: " << owningCard->getName() << " tapped.\n";
        return;
    }
    cout << "VinesnatcherAction: OwningCard and OwningPlayer are required.\n";
    throw;
}

void VinesnatcherTap::onReceiveSelection(std::list<Card*> cards)
{
    auto card = *cards.begin();
    cout << "VinesnatcherAction: " << owningCard->getName() << " deals 2 damage to " << card->getName() << ".\n";
    card->takeDamage(2);
}