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
        FMana cardCost = cardToPreview.cost;
        costDisplayRed.setFillColor(Settings::RedColor);
        costDisplayRed.setString(to_string(cardCost.Red));
        costDisplayRed.setFont(font);
        costDisplayRed.setScale(0.5, 0.5);
        costDisplayGreen.setFillColor(Settings::GreenColor);
        costDisplayGreen.setString(to_string(cardCost.Green));
        costDisplayGreen.setFont(font);
        costDisplayGreen.setScale(0.5, 0.5);
        costDisplayBlue.setFillColor(Settings::BlueColor);
        costDisplayBlue.setString(to_string(cardCost.Blue));
        costDisplayBlue.setFont(font);
        costDisplayBlue.setScale(0.5, 0.5);
        costDisplayBlack.setFillColor(Settings::BlackColor);
        costDisplayBlack.setString(to_string(cardCost.Black));
        costDisplayBlack.setFont(font);
        costDisplayBlack.setScale(0.5, 0.5);
        costDisplayWhite.setFillColor(Settings::WhiteColor);
        costDisplayWhite.setString(to_string(cardCost.White));
        costDisplayWhite.setFont(font);
        costDisplayWhite.setScale(0.5, 0.5);
    }
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

    void setPosition(sf::Vector2f newPosition) override{
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