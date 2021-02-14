#include "Bar.h"
#include "../Player.h"

Bar::Bar(int width, int height, sf::Color bgColor, sf::Color fgColor)
{
    barSize.x = width;
    barSize.y = height;
    this->BGColor = bgColor;
    this->FGColor = fgColor;
}
Bar::Bar(sf::Color bgColor, sf::Color fgColor, int rotation)
{
    this->BGColor = bgColor;
    this->FGColor = fgColor;
    setRotation(rotation);
}
Bar::Bar(int width, int height)
{
    barSize.x = width;
    barSize.y = height;
}
Bar::Bar()
{
}

void Bar::updateBG(){
    Background.setSize(barSize);
    Background.setOrigin(barSize / 2.0f);
    Background.setPosition(getPosition());
    Background.setFillColor(BGColor);
}

void Bar::updateFG(){
    float fgHeight = barSize.y - 2*offset;
    float fgWidth = (barSize.x - 2*offset) * amount;
    float fgOrigY = barSize.y / 2.0f - offset;
    float fgOrigX = barSize.x / 2.0f - offset;
    Foreground.setSize({fgWidth, fgHeight});
    Foreground.setOrigin({fgOrigX, fgOrigY});
    Foreground.setPosition(getPosition());
    Foreground.setFillColor(FGColor);
}

void Bar::setDimensions(sf::Vector2f dimensions)
{
    barSize = dimensions;
    updateBG();
    updateFG();
}

void Bar::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(Background);
    target.draw(Foreground);
}

void Bar::setFillFactor(float factor)
{
    amount = std::min(std::max(0.0f, factor), 1.0f);
    updateFG();
}

void Bar::setFGColor(sf::Color Color)
{
    Foreground.setFillColor(Color);
    this->FGColor = Color;
}

sf::Color Bar::getFGColor()
{
    return this->FGColor;
}

void Bar::setBGColor(sf::Color Color)
{
    Background.setFillColor(Color);
    this->BGColor = Color;
}

void Bar::setPosition(sf::Vector2f newPosition)
{
    Placeable::setPosition(newPosition);
    Background.setPosition(newPosition);
    Foreground.setPosition(newPosition);
    updateBG();
    updateFG();
}

void Bar::setRotation(float newRotation)
{
    Placeable::setRotation(newRotation);
    Foreground.setRotation(newRotation);
    Background.setRotation(newRotation);
    updateBG();
    updateFG();
}
