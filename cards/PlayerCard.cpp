#include "PlayerCard.h"

PlayerCard::PlayerCard(UISystem *ui) : Card(ui){};
void PlayerCard::onCardDeath()
{
    cout << "I lost the round!\n";
}
