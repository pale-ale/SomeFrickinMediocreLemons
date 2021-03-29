#pragma once
#include "Bar.h"
#include "../ManaType.h"
#include "../Settings.h"
#include <memory>

class ManaBars: public UIElement{
    public:
    ManaBars(UISystem* ui, const unsigned int width, const unsigned int height);
    void updateManaBars(FMana* mana);
    virtual void initializeSubComponents() override;
    private:
    const unsigned int width;
    const unsigned int height;
    const int maxMana = 20;
    shared_ptr<Bar> blackManaBar = std::make_shared<Bar>(ui, Settings::darkGrayColor, Settings::blackColor);
    shared_ptr<Bar> blueManaBar  = std::make_shared<Bar>(ui, Settings::darkGrayColor, Settings::blueColor);
    shared_ptr<Bar> greenManaBar = std::make_shared<Bar>(ui, Settings::darkGrayColor, Settings::greenColor);
    shared_ptr<Bar> redManaBar   = std::make_shared<Bar>(ui, Settings::darkGrayColor, Settings::redColor);
    shared_ptr<Bar> whiteManaBar = std::make_shared<Bar>(ui, Settings::darkGrayColor, Settings::whiteColor);
    list<shared_ptr<Bar>> ManaBarList = {
        blackManaBar,
        blueManaBar,
        greenManaBar,
        redManaBar,
        whiteManaBar
        };
};