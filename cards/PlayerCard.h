#pragma once

#include "../Card.h"

class PlayerCard : public Card
{
public:
    PlayerCard(UISystem *ui);
    virtual void onCardDeath() override;

    virtual void setupActions() override {}
    virtual void setupButtonBinding() override {}
};