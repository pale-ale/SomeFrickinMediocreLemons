//wip please do not modify will be edited on Saturday
#pragma once

#include <iostream>
#include "UISystem.h"
#include "sstream"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../events/EventCallback.h"
using std::cout;
using std::endl;

class TextBox : public UIElement{
    public:
    TextBox(UISystem* ui, sf::Vector2f size={Settings::defaultWidth,Settings::defaultHeight},unsigned int fontsize = Settings::fontSize, string content="", bool autoresize=true);
    //TextBox(UISystem* ui);
    unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    //return false, if text does not fit even with new line after each word and autoresize false
    bool changeContent(string content);
    bool changeCharacterSize(unsigned int size);
    bool changeSize(sf::Vector2f size);
    virtual void setPosition(const sf::Vector2f &newPosition) override;
	virtual void setRotation(const float &newRotation) override;
    virtual void setScale(float xScale, float yScale) override;

    private:
    //add ui listener
    //show text when hovering over Textbox
    virtual void initializeSubComponents() override;
    virtual bool OnBeginMouseover () override;
    virtual bool OnEndMouseover () override;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        target.draw(uicontent);
    }
    bool autoresize;
    sf::Vector2f size;

    unsigned int fontsize = 10;
    sf::Text uicontent;
    string content;
    bool UpdateContent();
    //update when changing dimensions
    void CalculateWidth();
};