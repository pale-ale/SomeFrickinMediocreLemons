#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../ManaType.h"
using std::cout;
using std::endl;

class Player;

class Bar : public UIElement{
    public:
    Bar();
    //void setOwner(Player *);
    void setLifePointbase(int);
    void setCurrent(int);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
   
    protected:
    typedef struct {FMana* fmana; sf::Rect<float> Shape;} Manabar;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    private:
    const int BarWidth = 40;
    const int BarHeight = 10;
    const int offset = 2;
    int LifePointbase;
    sf::RectangleShape HealthBar;
    sf::RectangleShape Background;
    Player* owner = nullptr;
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    list<Manabar> manabars;
};