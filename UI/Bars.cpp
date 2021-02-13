#include "Bars.h"
#include "../Player.h"

Bar::Bar(int width, int height, sf::Color bgColor, sf::Color fgColor){
    this->barHeight = height;
    this->barWidth = width;
    this->BGColor = bgColor;
    this->FGColor = fgColor;
    initializeBar();
}
Bar::Bar(sf::Color bgColor, sf::Color fgColor){
    this->BGColor = bgColor;
    this->FGColor = fgColor;
    initializeBar();
}
Bar::Bar(int width, int height){
    this->barWidth = width;
    this->barHeight = height;
    initializeBar();
}
Bar::Bar(){
    initializeBar();
}
void Bar::initializeBar(){
    Background.setSize(sf::Vector2f(barWidth,barHeight));
    Background.setFillColor(sf::Color(this->BGColor));
    Background.setOrigin(Background.getSize()/2.0f);
    Foreground.setSize(sf::Vector2f(barWidth-offset,barHeight-offset));
    Foreground.setFillColor(sf::Color(this->FGColor));
    Foreground.setOrigin(Foreground.getSize()/2.0f);
    Foreground.setPosition(Background.getPosition().x+(offset/2),Background.getPosition().y+(offset/2));
}
void Bar::setMax(int newMax){
    this->max = newMax;
}
void Bar::setDimensions(int Width, int Height){
    this->barWidth=Width;
    this->barHeight=Height;
    Background.setSize(sf::Vector2f(barWidth,barHeight));
    Foreground.setSize(sf::Vector2f(barWidth-offset,barHeight-offset));
}
void Bar::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(Background);
    target.draw(Foreground);
}
void Bar::setCurrent(int newCurrent){
    current = newCurrent;
    float xScale = std::min((float)current/max, 1.0f);
    Foreground.setSize(sf::Vector2f(barWidth*xScale, barHeight));
}
void Bar::setFGColor(sf::Color Color){
    Foreground.setFillColor(Color);
    this->FGColor=Color;
}
sf::Color Bar::getFGColor(){
    return this->FGColor;
}
void Bar::setBGColor(sf::Color Color){
    Background.setFillColor(Color);
    this->BGColor=Color;
}
void Bar::setPosition(sf::Vector2f newPosition)
{
	Placeable::setPosition(newPosition);
    Background.setPosition(newPosition);
    Foreground.setPosition(newPosition);
}
void Bar::setRotation(float newRotation){
    auto delta = transform.getRotation() - newRotation;
    Placeable::setRotation(delta);
	Foreground.setRotation(delta);
    Background.setRotation(delta);
}