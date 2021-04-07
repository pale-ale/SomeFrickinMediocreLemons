#pragma once

#include "../IAction.h"
#include <string>
#include <iostream>
#include "../Card.h"
#include "../Player.h"

using std::string;

class DefaultAttack : public IAction
{
public:
    DefaultAttack(Player *player, Card *card);
    sf::Texture const &getActionImage() const override
    {
        return image;
    }
    std::string getActionString() const override
    {
        return text;
    }
    bool getActionEnabled() const override
    {
        return bIsEnabled;
    }
    bool getNeedsTargeting() const override
    {
        return true;
    }
    CardSelectionInfo getTargetingInfo() const override
    {
        return {};
    }
    void triggerAction() override
    {
        std::cout << "Attacking!\n";
    };
    void onReceiveSelection(std::list<Card*> cards) override;
    void setOwningPlayer(Player* newPlayer) override
    {
        owningPlayer = newPlayer;
    } 

    Player *owningPlayer;
    Card *owningCard;


private:
    sf::Texture image;
    std::string text = "Attack";
    bool bIsEnabled = true;
};