#include "ManaBars.h"

ManaBars::ManaBars(UISystem* ui, const unsigned int width, const unsigned int height):
UIElement(ui), width{width}, height{height}
{name = "ManaBars";}

void ManaBars::initializeSubComponents(){
    int o = 0;
    float offset = (float)height/5;
    sf::Vector2f dims = {(float)width, (float)height/5};
    for (auto bar : ManaBarList)
    {
        bar->setDimensions(dims);
        bar->setPosition(sf::Vector2f(0, o * offset - o*(float)bar->offset/2));
        bar->reparent(this);
        bar->initializeSubComponents();
        addChild(bar);
        o++;
    }
}

void ManaBars::updateManaBars(FMana *Fmana)
{
    blackManaBar->setFillFactor((float)Fmana->Black / maxMana);
    blueManaBar->setFillFactor((float)Fmana->Blue / maxMana);
    greenManaBar->setFillFactor((float)Fmana->Green / maxMana);
    redManaBar->setFillFactor((float)Fmana->Red / maxMana);
    whiteManaBar->setFillFactor((float)Fmana->White / maxMana);
}