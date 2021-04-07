#include "DefaultAttack.h"

DefaultAttack::DefaultAttack(Player *player, Card *card): owningPlayer{player}, owningCard{card}{
  if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png"))
        {
            cout << "DefaultAttackAction: Error loading image '" 
                 << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
        }
}
void DefaultAttack::onReceiveSelection(list<Card*> cards)
{
    (*cards.begin())->takeDamage(owningCard->getPower());
}