#pragma once

#include "../Card.h"
#include "../IAction.h"
#include <iostream>
#include "../Player.h"
#include "../Settings.h"
#include <string>

using std::string;
using std::cout;

class VinesnatcherTap : public IAction
{
public:
    VinesnatcherTap(Player *player, Card *card);
    void triggerAction() override;
    void onReceiveSelection(std::list<Card*> cards) override;
    
    sf::Texture const &getActionImage() const override{return image;}
    std::string getActionString() const override{return text;}
    bool getActionEnabled() const override{return bIsEnabled;}
    bool getNeedsTargeting() const override{return true;}
    CardSelectionInfo getTargetingInfo() const override{return {};}
    void setOwningPlayer(Player* newPlayer){owningPlayer = newPlayer;}

    Player *owningPlayer;
    Card *owningCard;

private:
    sf::Texture image;
    std::string text = "Tap";
    bool bIsEnabled = true;
};