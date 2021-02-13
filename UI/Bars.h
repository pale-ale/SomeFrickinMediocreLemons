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
    Bar(int, int, sf::Color, sf::Color);
    Bar(sf::Color,sf::Color);
    Bar(int, int);
    Bar();
    void setMax(int);
    void setDimensions(int,int);
    void setCurrent(int);
    void setFGColor(sf::Color);
    void setBGColor(sf::Color);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
    
   
    protected:
    typedef struct {FMana* fmana; sf::Rect<float> Shape;} Manabar;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    int barWidth = 40;
    int barHeight = 10;
    const int offset = 2;
    int max = 0;
    int current = 0;
    sf::Color FGColor = {255,0,0,255};
    sf::Color BGColor = {0,0,0,255};
    sf::RectangleShape Foreground;
    sf::RectangleShape Background;
    unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    list<Manabar> manabars;
    void initializeBar();
};