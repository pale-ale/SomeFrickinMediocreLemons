#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Events/EventCallback.h"


class Button : public UIElement{
    public:
    Button(sf::Rect<float> rect = {0,0,50,50});
    IEventCallback* callback; 

    virtual void OnMouseButtonDown()override {cout << "Calling delegate!\n"; (*callback)();}
    virtual void SetPosition(sf::Vector2f newPosition)override;
    virtual void SetRotation(float newRotation)override;
    
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