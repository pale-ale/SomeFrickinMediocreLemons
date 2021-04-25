#pragma once

#include <iostream>
#include <string>

#include "../IAction.h"

using std::string;

class Card;
class Player;

class DefaultAttack : public IAction
{
public:
    DefaultAttack(Player *player, Card *card);
    void onReceiveSelection(std::list<Card *> cards) override;

    sf::Texture const &getActionImage() const override { return image; }
    std::string getActionString() const override { return text; }
    bool getActionEnabled() const override { return bIsEnabled; }
    bool getNeedsTargeting() const override { return true; }
    CardSelectionInfo getTargetingInfo() const override { return {}; }
    void triggerAction() override { std::cout << "Attacking!\n"; };
    void setOwningPlayer(Player *newPlayer) override { owningPlayer = newPlayer; }

    Player *owningPlayer;
    Card *owningCard;

private:
    sf::Texture image;
    std::string text = "Atk: Deal damage equal to [Pow] to target enemy creature in battle zone.";
    bool bIsEnabled = true;
};