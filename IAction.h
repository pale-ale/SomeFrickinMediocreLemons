#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class IAction{
    public:
    virtual sf::Texture const &getActionImage() const = 0;
    virtual std::string getActionString() const = 0;
    virtual bool getActionEnabled() const = 0;
    virtual void triggerAction() = 0;
};