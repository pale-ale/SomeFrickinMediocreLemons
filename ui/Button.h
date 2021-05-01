#pragma once

#include <iostream>
#include <memory.h>
#include <SFML/Graphics.hpp>

#include "UIElement.h"

#include "../Settings.h"

template<typename ...T>
class IEventCallback;
class UISystem;

class Button : public UIElement{
    public:
    Button(UISystem* ui,
           sf::Color defaultColor = {150,150,150,100}, 
           sf::Color mouseOverColor = {200,200,200,100},
           vector<sf::Vector2f> corners = {{-25, -37.5}, {-25, 37.5}, {25, 37.5}, {25, -37.5}}
           );
    ~Button();

    std::shared_ptr<IEventCallback<>> onMouseDownCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onMouseUpCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onClickCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onDragStartCallback = nullptr;
    std::shared_ptr<IEventCallback<const sf::Vector2f&>> onDragMoveCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onDragEndCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onBeginMouseoverCallback = nullptr;
    std::shared_ptr<IEventCallback<>> onEndMouseoverCallback = nullptr;
    bool handleEvent = true;
    bool isPressed = false;

    virtual bool OnMouseButtonDown(const sf::Vector2f &mouseLocation) override;
    virtual bool OnMouseButtonUp(const sf::Vector2f &mouseLocation) override;
    virtual bool OnBeginMouseover() override;
    virtual bool OnEndMouseover() override;
    virtual void OnClick() override;
    virtual void OnDragStart() override;
    virtual void OnDragMove(const sf::Vector2f &newPos) override;
    virtual void OnDragEnd() override;
    virtual void setPosition(const sf::Vector2f &newPosition) override;
    virtual void setRotation(const float &newRotation) override;
    virtual void setScale(float xScale, float yScale) override;
    using UIElement::setScale;
    virtual void setHitbox(const vector<sf::Vector2f> &newHitbox) override;

    virtual void initializeSubComponents() override;
	
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
    void updateShape();
    sf::ConvexShape buttonShape;
    sf::Color defaultColor;
    sf::Color mouseOverColor;
};