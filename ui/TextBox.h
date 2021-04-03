//wip please do not modify will be edited on Saturday
#pragma once

#include <iostream>
#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Settings.h"
#include "../events/EventCallback.h"
using std::cout;
using std::endl;

class TextBox : public UIElement{
    public:
    TextBox(UISystem* ui, sf::Vector2f size, string content, bool autoresize);
    sf::Text BarInfo;
    unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    //return false, if text does not fit even with new line after each word
    bool ChangeContent(char * content);
    bool ChangeCharacterSize(unsigned int size);
    virtual void setPosition(const sf::Vector2f &newPosition) override;
	virtual void setRotation(const float &newRotation) override;

    private:
    //add ui listener
    //show text when hovering over Textbox
    virtual void initializeSubComponents() override;
    virtual bool OnBeginMouseover () override;
    virtual bool OnEndMouseover () override;
    bool autoresize;

    unsigned int fontsize = 10;
    sf::Text uicontent;
    string content;
    bool UpdateContent();
    //update when changing dimensions
    void CalculateWidth();
};