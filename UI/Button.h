#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../Events/EventCallback.h"


class Button : public UIElement{
    public:
    Button(sf::Rect<float> rect = {0,0,50,50});
    IEventCallback* callback = nullptr;
    bool handleEvent = true;

    virtual bool OnMouseButtonDown() override;
    virtual void setPosition(sf::Vector2f newPosition)override;
    virtual void setRotation(float newRotation)override;
    
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