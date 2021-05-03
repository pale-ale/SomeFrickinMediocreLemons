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
    std::shared_ptr<Bar> blackManaBar = std::make_shared<Bar>(ui, sf::Color{50,50,50,255}, sf::Color{  0,  0,  0,255});
    std::shared_ptr<Bar> blueManaBar  = std::make_shared<Bar>(ui, sf::Color{50,50,50,255}, sf::Color{  0,  0,255,255});
    std::shared_ptr<Bar> greenManaBar = std::make_shared<Bar>(ui, sf::Color{50,50,50,255}, sf::Color{  0,255,  0,255});
    std::shared_ptr<Bar> redManaBar   = std::make_shared<Bar>(ui, sf::Color{50,50,50,255}, sf::Color{255,  0,  0,255});
    std::shared_ptr<Bar> whiteManaBar = std::make_shared<Bar>(ui, sf::Color{50,50,50,255}, sf::Color{255,255,255,255});
    list<std::shared_ptr<Bar>> ManaBarList = {
        blackManaBar,
        blueManaBar,
        greenManaBar,
        redManaBar,
        whiteManaBar
        };
};