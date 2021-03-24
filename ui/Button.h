#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../events/EventCallback.h"


class Button : public UIElement{
    public:
    Button(UISystem* ui,
           sf::Rect<float> rect = {0,0,50,50}, 
           sf::Color color = {255, 0, 255, Settings::bEnableButtonTint ? 100 : 0});
    ~Button(){
        cout << "Button: Destroying button.\n";
        if(ui){
            ui->removeListener(this);
        }
    }
    shared_ptr<IEventCallback> onMouseDownCallback = nullptr;
    shared_ptr<IEventCallback> onMouseUpCallback = nullptr;
    shared_ptr<IEventCallback> onBeginMouseoverCallback = nullptr;
    shared_ptr<IEventCallback> onEndMouseoverCallback = nullptr;
    bool handleEvent = true;
    bool isPressed = false;

    virtual bool OnMouseButtonDown() override;
    virtual bool OnMouseButtonUp() override;
    virtual bool OnBeginMouseover() override;
    virtual bool OnEndMouseover() override;
    virtual void setPosition(sf::Vector2f newPosition) override;
    virtual void setSize(const sf::Vector2f &newSize) override;

    virtual void setRotation(float newRotation) override;
	
    void setDefaultColor(sf::Color color){
        defaultColor = color;
        buttonShape.setFillColor(defaultColor);
    }
	void setMouseoverColor(sf::Color color){
        mouseOverColor = color;
    }
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(buttonShape);
    }

    private:
    sf::FloatRect rect;
    sf::RectangleShape buttonShape;
    sf::Sprite buttonSprite;
    sf::Texture buttonTexture;
    sf::Color defaultColor = {255,0,255,0};
    sf::Color mouseOverColor = {255,0,255,100};
};