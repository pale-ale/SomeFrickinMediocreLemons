#pragma once
#include "Bars.h"
#include "../ManaType.h"
#include "../Settings.h"

class ManaBar: public Bar{
    public:
    ManaBar();
    ManaBar(sf::Color,sf::Color);
    ManaBar(int,int,sf::Color,sf::Color);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
    EManaType getManaType();
    private:
    EManaType ManaType;
};

class ManaBars{
    public:
    ManaBars(const unsigned int, const unsigned int, const unsigned int, const unsigned int);
    private:
    ManaBar blackManaBar = ManaBar(Settings::BlackColor, Settings::BlackColor);
    ManaBar blueManaBar = ManaBar(Settings::BlackColor,Settings::BlueColor);
    ManaBar greenManaBar = ManaBar(Settings::BlackColor, Settings::GreenColor);
    ManaBar redManaBar = ManaBar(Settings::BlackColor, Settings::RedColor);
    ManaBar whiteManaBar = ManaBar(Settings::BlackColor, Settings::WhiteColor);
    list<ManaBar*> ManaBarList = {&blackManaBar,&blueManaBar,&greenManaBar,&redManaBar,&whiteManaBar};

};