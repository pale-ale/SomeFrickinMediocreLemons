#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../Events/EventCallback.h"


class Button : public UIElement{
    public:
    Button(sf::Rect<float> rect = {0,0,50,50}, 
           sf::Color color = {255, 0, 255, Settings::bEnableButtonTint ? 100 : 0});
    IEventCallback* onClickCallback = nullptr;
    IEventCallback* onBeginMouseoverCallback = nullptr;
    IEventCallback* onEndMouseoverCallback = nullptr;
    bool handleEvent = true;
    sf::Color defaultColor = {255,0,255,0};
    sf::Color mouseOverColor = {255,0,255,100};

    virtual bool OnMouseButtonDown() override;
    virtual bool OnBeginMouseover() override;
    virtual bool OnEndMouseover() override;
    virtual void setPosition(sf::Vector2f newPosition)override;
    virtual void setRotation(float newRotation)override;
	void setColor(sf::Color color){
        buttonShape.setFillColor(color);
    }
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(buttonShape);
    }

    private:
    sf::Rect<float> rect;
    sf::RectangleShape buttonShape;
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture;
};