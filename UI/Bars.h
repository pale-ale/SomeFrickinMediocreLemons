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
    void setMax(int);
    void setCurrent(int);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
   
    protected:
    typedef struct {FMana* fmana; sf::Rect<float> Shape;} Manabar;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    private:
    const int barWidth = 40;
    const int barHeight = 10;
    const int offset = 2;
    int max = 0;
    int current = 0;
    sf::RectangleShape Foreground;
    sf::RectangleShape Background;
    unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    list<Manabar> manabars;
};