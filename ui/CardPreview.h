#pragma once

#include "UISystem.h"
#include <SFML/Graphics.hpp>
#include "../Card.h"
#include "../Settings.h"

class CardPreview : public UIElement
{
public:
    CardPreview(UISystem* ui, const Card* cardToPreview);
    const sf::Vector2f titlePos = {Settings::defaultWidth/2, (int)Settings::defaultHeight/2 - 110};
    const sf::Vector2f costPos = {Settings::defaultWidth/2 + 70, (int)Settings::defaultHeight/2 - 38};
    const sf::Vector2f backgroundPos = {Settings::defaultWidth/2, Settings::defaultHeight/2};
    const sf::Vector2f imagePos = {Settings::defaultWidth/2, Settings::defaultHeight/2-30};
    const sf::Vector2f descriptionPos = {Settings::defaultWidth/2, Settings::defaultHeight/2 + 25};
    const sf::Vector2f size = {200, 350};
    sf::Font font;
    sf::Text cardTitle;
    sf::Text costDisplayRed;
    sf::Text costDisplayGreen;
    sf::Text costDisplayBlue;
    sf::Text costDisplayBlack;
    sf::Text costDisplayWhite;
    sf::Text description;
    sf::Sprite cardImage;
    sf::RectangleShape background;

    void setPosition(const sf::Vector2f &newPosition) override{
        UIElement::setPosition(newPosition);
        cardTitle.setPosition(titlePos);
        background.setPosition(backgroundPos);
        cardImage.setPosition(imagePos);
        description.setPosition(descriptionPos);
        costDisplayRed.setPosition(costPos + sf::Vector2f{0, -30});
        costDisplayGreen.setPosition(costPos + sf::Vector2f{0, -15});
        costDisplayBlue.setPosition(costPos + sf::Vector2f{0, 0});
        costDisplayBlack.setPosition(costPos + sf::Vector2f{0, 15});
        costDisplayWhite.setPosition(costPos + sf::Vector2f{0, 30});
    }

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        UIElement::draw(target, state);
        target.draw(background);
        target.draw(cardImage);
        target.draw(description);
        target.draw(cardTitle);
        target.draw(costDisplayRed);
        target.draw(costDisplayGreen);
        target.draw(costDisplayBlue);
        target.draw(costDisplayBlack);
        target.draw(costDisplayWhite);
    }
};