#pragma once

#include <iostream>
#include <string>

#include "../Card.h"
#include "../IAction.h"
#include "../Player.h"
#include "../Settings.h"

using std::string;
using std::cout;

class FlamestrikePlay : public IAction
{
public:
    FlamestrikePlay(Player *player, Card *card);
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
    std::string text = "Select a target enemy creature in a battle zone to deal 3 damage to it.";
    bool bIsEnabled = true;
};