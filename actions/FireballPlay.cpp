#include "FireballPlay.h"

FireballPlay::FireballPlay(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
{
    if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "FireballTapTexture.png"))
    {
        cout << "FireballPlay: Error loading image '" 
                << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
    }
}

void FireballPlay::triggerAction()
{
    cout << "FireballPlay: Clicked\n";
    if (owningPlayer && owningCard)
    {
        owningPlayer->awaitingSelection = this;
        CardSelectionInfo csi;
        csi.canAttackHeroDirectly = true;
        cout << "FireballPlay: " << owningCard->label << " requesting selection.\n";
        owningPlayer->startSelection(csi);
        cout << "FireballPlay: " << owningCard->label << " tapped.\n";
        return;
    }
    cout << "FireballPlay: OwningCard and OwningPlayer are required.\n";
    throw;
}

void FireballPlay::onReceiveSelection(std::list<Card*> cards)
{
    
    auto card = *cards.begin();
    cout << "FireballPlay: " << owningCard->label << " deals 3 damage to " << card->label << ".\n";
    card->takeDamage(2);
}