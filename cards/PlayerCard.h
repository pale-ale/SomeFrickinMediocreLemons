#pragma once

#include "../Card.h"

class Player;

class PlayerCard : public Card
{
public:
    PlayerCard(UISystem *ui);
    virtual void onCardDeath() override;
    virtual void takeDamage(const int& amount) override;
    virtual void setupActions() override {}
};