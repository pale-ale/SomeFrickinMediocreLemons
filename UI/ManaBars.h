#pragma once
#include "Bar.h"
#include "../ManaType.h"
#include "../Settings.h"

class ManaBars: public UIElement{
    public:
    ManaBars(const unsigned int width, const unsigned int height);
    void updateManaBars(FMana* mana);
   
    private:
    const int maxMana = 20;
    Bar blackManaBar = Bar(Settings::DarkGrayColor, Settings::BlackColor);
    Bar blueManaBar  = Bar(Settings::DarkGrayColor, Settings::BlueColor);
    Bar greenManaBar = Bar(Settings::DarkGrayColor, Settings::GreenColor);
    Bar redManaBar   = Bar(Settings::DarkGrayColor, Settings::RedColor);
    Bar whiteManaBar = Bar(Settings::DarkGrayColor, Settings::WhiteColor);
    list<Bar*> ManaBarList = {&blackManaBar,&blueManaBar,&greenManaBar,&redManaBar,&whiteManaBar};
};