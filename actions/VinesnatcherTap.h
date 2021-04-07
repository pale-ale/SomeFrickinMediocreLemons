#pragma once

#include "../IAction.h"
#include <string>
#include <iostream>

using std::string;

class VinesnatcherTap : public IAction
{
public:
    VinesnatcherTap(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
    {
        if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "VinesnatcherTapTexture.png"))
        {
            cout << "VinesnatcherTap: Error loading image '" 
                 << Settings::programDir + string(Settings::relativeAssetActionPath) + "DefaultAttackAction.png'.\n";
        }
    }
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
    void onReceiveSelection(list<Card*> cards) override
    {
        auto card = *cards.begin();
        cout << "VinesnatcherAction: " << owningCard->getName() << " deals 2 damage to " << card->getName() << ".\n";
        card->takeDamage(2);
    }
    void setOwningPlayer(Player* newPlayer)
    {
        owningPlayer = newPlayer;
    }
    Player *owningPlayer;
    Card *owningCard;

private:
    sf::Texture image;
    std::string text = "Tap";
    bool bIsEnabled = true;
};