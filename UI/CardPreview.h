#pragma once

#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../card.h"
#include "../Settings.h"

class CardPreview : public UIElement
{
public:
    CardPreview(UISystem* ui, const card &cardToPreview):
    UIElement(ui)
    {
        font.loadFromFile(Settings::validFontPath);
        cardTitle.setFont(font);
        description.setFont(font);
        cardTitle.setString(cardToPreview.getName());
        description.setString(cardToPreview.getDescription());
        //description.setCharacterSize(10);
        description.setScale(.2,.2);
        cardTitle.setOrigin({cardTitle.getLocalBounds().width/2, cardTitle.getLocalBounds().height/2});
        description.setOrigin({description.getLocalBounds().width/2, description.getLocalBounds().height/2});
        background.setFillColor({50,50,50,100});
        background.setSize(size);
        background.setOrigin(size/2.0f);
        cardImage.setTexture(*(cardToPreview.getTexture().get()), true);
        cardImage.setScale(2.5,2.5);
        cardImage.setOrigin({cardImage.getLocalBounds().width/2, cardImage.getLocalBounds().height/2});
    }
    const sf::Vector2f titlePos = {Settings::defaultWidth/2, (int)Settings::defaultHeight/2 - 110};
    const sf::Vector2f backgroundPos = {Settings::defaultWidth/2, Settings::defaultHeight/2};
    const sf::Vector2f imagePos = {Settings::defaultWidth/2, Settings::defaultHeight/2-30};
    const sf::Vector2f descriptionPos = {Settings::defaultWidth/2, Settings::defaultHeight/2 + 25};
    const sf::Vector2f size = {200, 350};
    sf::Font font;
    sf::Text cardTitle;
    sf::Text description;
    sf::Sprite cardImage;
    sf::RectangleShape background;

    void setPosition(sf::Vector2f newPosition) override{
        UIElement::setPosition(newPosition);
        cardTitle.setPosition(titlePos);
        background.setPosition(backgroundPos);
        cardImage.setPosition(imagePos);
        description.setPosition(descriptionPos);
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