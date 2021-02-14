#pragma once

#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../card.h"
#include "../Settings.h"

class CardPreview : public UIElement
{
public:
    CardPreview(const card &cardToPreview)
    {
        font.loadFromFile(Settings::validFontPath);
        cardTitle.setFont(font);
        cardTitle.setString(cardToPreview.getName());
        cardTitle.setOrigin({cardTitle.getLocalBounds().width/2, cardTitle.getLocalBounds().height/2});
        background.setFillColor(Settings::DarkGrayColor);
        background.setSize(size);
        background.setOrigin(size/2.0f);
    }
    sf::Vector2f titlePosition = {Settings::defaultWidth/2, Settings::defaultHeight/2 - 75};
    sf::Vector2f backgroundPosition = {Settings::defaultWidth/2, Settings::defaultHeight/2};
    sf::Vector2f size = {200, 350};
    sf::Font font;
    sf::Text cardTitle;
    sf::Text description;
    sf::Sprite cardImage;
    sf::RectangleShape background;

    void setPosition(sf::Vector2f newPosition) override{
        UIElement::setPosition(newPosition);
        cardTitle.setPosition(titlePosition);
        background.setPosition(backgroundPosition);
    }

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        UIElement::draw(target, state);
        target.draw(background);
        target.draw(cardImage);
        target.draw(description);
        target.draw(cardTitle);
    }
};