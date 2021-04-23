#include "PlayerCard.h"
#include "../Player.h"

PlayerCard::PlayerCard(UISystem *ui) : Card(ui){};

void PlayerCard::takeDamage(const int &amount){
    Card::takeDamage(amount);
    if (owner){
        owner->setLifePoints(max(0, owner->getLifePoints() - amount));
    }   
}

void PlayerCard::onCardDeath()
{
    cout << "I lost the round!\n";
}
