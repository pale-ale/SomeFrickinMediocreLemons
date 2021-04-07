#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "CardSelectionInfo.h"
#include <list>

class Card;
class Player;

class IAction{
    public:
    virtual sf::Texture const &getActionImage() const = 0;
    virtual std::string getActionString() const = 0;
    virtual bool getActionEnabled() const = 0;
    virtual bool getNeedsTargeting() const = 0;
    virtual CardSelectionInfo getTargetingInfo() const = 0;
    virtual void triggerAction() = 0;
	virtual void onReceiveSelection(std::list<Card*> cards) = 0;
    virtual void setOwningPlayer(Player* newPlayer) = 0;
};