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
    Bar(UISystem* ui, int width, int height, sf::Color bgcolor, sf::Color fgColor);
    Bar(UISystem* ui, sf::Color bgColor, sf::Color fgColor, int rotation = 0);
    Bar(UISystem* ui, int width, int height);
    Bar(UISystem* ui);
    void setDimensions(sf::Vector2f);
    //set the "fullness" of the bar (0=empty, 1=full)
    void setFillFactor(float factor);
    float getFillFactor() const{return amount;};
    void setFGColor(sf::Color);
    sf::Color getFGColor();
    void setBGColor(sf::Color);
    virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
    const int offset = 1;
    
   
    protected:
    typedef struct {FMana* fmana; sf::Rect<float> Shape;} Manabar;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    
    private:
    sf::Vector2f barSize = {40, 10};
    float amount = 0;
    sf::Color FGColor = {255,0,0,255};
    sf::Color BGColor = {0,0,0,255};
    sf::RectangleShape Foreground;
    sf::RectangleShape Background;
    unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    list<Manabar> manabars;
    void updateBG();
    void updateFG();
};