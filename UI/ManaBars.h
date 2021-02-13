#pragma once
#include "Bars.h"
#include "../ManaType.h"
#include "../Settings.h"

/*class ManaBar: public Bar{
    public:
    ManaBar();
    ManaBar(sf::Color,sf::Color);
    ManaBar(int,int,sf::Color,sf::Color);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
    EManaType getManaType();
    private:
    EManaType ManaType;
};*/

class ManaBars: public UIElement{
    public:
    ManaBars(const int, const unsigned int, const unsigned int);
    void updateManaBars(FMana* mana);
    virtual void setPosition(sf::Vector2f newPosition) override;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    

    private:
    int offset;
    Bar blackManaBar = Bar(Settings::BlackColor, Settings::BlackColor);
    Bar blueManaBar = Bar(Settings::BlackColor,Settings::BlueColor);
    Bar greenManaBar = Bar(Settings::BlackColor, Settings::GreenColor);
    Bar redManaBar = Bar(Settings::BlackColor, Settings::RedColor);
    Bar whiteManaBar = Bar(Settings::BlackColor, Settings::WhiteColor);
    list<Bar*> ManaBarList = {&blackManaBar,&blueManaBar,&greenManaBar,&redManaBar,&whiteManaBar};

};