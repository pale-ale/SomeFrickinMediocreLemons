#pragma once
#include "Bar.h"
#include "../ManaType.h"
#include "../Settings.h"

class ManaBars: public UIElement{
    public:
    ManaBars(UISystem* ui, const unsigned int width, const unsigned int height);
    void updateManaBars(FMana* mana);
   
    private:
    const int maxMana = 20;
    Bar blackManaBar = Bar(ui, Settings::DarkGrayColor, Settings::BlackColor);
    Bar blueManaBar  = Bar(ui, Settings::DarkGrayColor, Settings::BlueColor);
    Bar greenManaBar = Bar(ui, Settings::DarkGrayColor, Settings::GreenColor);
    Bar redManaBar   = Bar(ui, Settings::DarkGrayColor, Settings::RedColor);
    Bar whiteManaBar = Bar(ui, Settings::DarkGrayColor, Settings::WhiteColor);
    list<Bar*> ManaBarList = {&blackManaBar,&blueManaBar,&greenManaBar,&redManaBar,&whiteManaBar};
};