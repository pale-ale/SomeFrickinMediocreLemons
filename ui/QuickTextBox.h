#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../events/EventCallback.h"
using std::cout;
using std::endl;


//This is a quick and probably dirty solution, since the actual textbox class is taking way too long
class QuickTextBox : public UIElement{
    public:
    QuickTextBox(UISystem* ui, string text="test", bool autoWrap=true);
    sf::Font font;
    void setText(const string &newText);
    void setCharacterSize(unsigned int newFontSize);
    virtual void setPosition(const sf::Vector2f &newPosition) override{
        UIElement::setPosition(newPosition);
        textDisplay.setPosition(newPosition);
    }
	virtual void setRotation(const float &newRotation) override{
        UIElement::setRotation(newRotation);
        textDisplay.setRotation(newRotation);
    }
    using UIElement::setScale;
    virtual void setScale(float xScale, float yScale) override{
        UIElement::setScale(xScale, yScale);
        textDisplay.setScale(xScale, yScale);
    }
    int maxCharacterCountPerLine = 20;

    private:
    bool autoWrap;
    unsigned int fontSize = 24;
    sf::Text textDisplay;
    string originalText;
    string formattedText;
    void updateContent();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        target.draw(textDisplay);
    }
};