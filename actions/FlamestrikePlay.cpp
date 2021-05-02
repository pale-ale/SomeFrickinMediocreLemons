#include "FlamestrikePlay.h"

FlamestrikePlay::FlamestrikePlay(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
{
    if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "VinesnatcherTapTexture.png"))
    {
        cout << "VinesnatcherTap: Error loading image '" 
                << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
    }
}

void FlamestrikePlay::triggerAction()
{
    cout << "VinesnatcherAction: Clicked\n";
    if (owningPlayer && owningCard)
    {
        owningPlayer->awaitingSelection = this;
        CardSelectionInfo csi;
        cout << "VinesnatcherAction: " << owningCard->label << " requesting selection.\n";
        owningPlayer->startSelection(csi);
        cout << "VinesnatcherAction: " << owningCard->label << " tapped.\n";
        return;
    }
    cout << "VinesnatcherAction: OwningCard and OwningPlayer are required.\n";
    throw;
}

void FlamestrikePlay::onReceiveSelection(std::list<Card*> cards)
{
    auto card = *cards.begin();
    cout << "VinesnatcherAction: " << owningCard->label << " deals 2 damage to " << card->label << ".\n";
    card->takeDamage(2);
}