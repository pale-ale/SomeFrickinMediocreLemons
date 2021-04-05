#include "../IAction.h"
#include <string>
#include "../Settings.h"
#include <iostream>

using std::cout;
using std::string;

class VinesnatcherTap : public IAction
{
public:
    VinesnatcherTap(Player *player, Card *card) : owningPlayer{player}, owningCard{card}
    {
        if (!image.loadFromFile(Settings::programDir + string(Settings::relativeAssetActionPath) + "VinesnatcherTapTexture.png"))
        {
            cout << "DefaultAttackAction: Error loading image '" 
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
    void triggerAction() override
    {
        cout << "VinesnatcherAction: Clicked\n";
        if (owningPlayer && owningCard)
        {
            owningPlayer->awaitingSelection = owningCard;
            CardSelectionInfo csi;
            cout << "VinesnatcherAction: " << owningCard->getName() << " requesting selection.\n";
            owningPlayer->startSelection(csi);
            cout << "VinesnatcherAction: " << owningCard->getName() << " tapped.\n";
        }
        else{
            cout << owningCard << ", " << owningPlayer << endl;
        }
    };
    Player *owningPlayer;
    Card *owningCard;

private:
    sf::Texture image;
    std::string text = "Tap";
    bool bIsEnabled = true;
};