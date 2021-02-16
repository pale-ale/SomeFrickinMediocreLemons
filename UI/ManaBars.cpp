#include "ManaBars.h"

ManaBars::ManaBars(UISystem* ui, const unsigned int width, const unsigned int height):
UIElement(ui)
{
    int o = 0;
    float offset = (float)height/5;
    sf::Vector2f dims = {(float)width, (float)height/5};
    for (Bar *i : ManaBarList)
    {
        i->setDimensions(dims);
        i->setPosition(sf::Vector2f(0, o * offset - o*(float)i->offset/2));
        i->attachTo(this);
        o++;
    }
}

void ManaBars::updateManaBars(FMana *Fmana)
{
    blackManaBar.setFillFactor((float)Fmana->Black / maxMana);
    blueManaBar.setFillFactor((float)Fmana->Blue / maxMana);
    greenManaBar.setFillFactor((float)Fmana->Green / maxMana);
    redManaBar.setFillFactor((float)Fmana->Red / maxMana);
    whiteManaBar.setFillFactor((float)Fmana->White / maxMana);
}