#pragma once
#include "Bar.h"
#include "../ManaType.h"
#include "../Settings.h"
#include <memory>

class ManaBars: public UIElement{
    public:
    ManaBars(UISystem* ui, const unsigned int width, const unsigned int height);
    void updateManaBars(FMana* mana);
   
    private:
    const int maxMana = 20;
    shared_ptr<Bar> blackManaBar = std::make_shared<Bar>(ui, Settings::DarkGrayColor, Settings::BlackColor);
    shared_ptr<Bar> blueManaBar  = std::make_shared<Bar>(ui, Settings::DarkGrayColor, Settings::BlueColor);
    shared_ptr<Bar> greenManaBar = std::make_shared<Bar>(ui, Settings::DarkGrayColor, Settings::GreenColor);
    shared_ptr<Bar> redManaBar   = std::make_shared<Bar>(ui, Settings::DarkGrayColor, Settings::RedColor);
    shared_ptr<Bar> whiteManaBar = std::make_shared<Bar>(ui, Settings::DarkGrayColor, Settings::WhiteColor);
    list<shared_ptr<Bar>> ManaBarList = {
        blackManaBar,
        blueManaBar,
        greenManaBar,
        redManaBar,
        whiteManaBar
        };
};