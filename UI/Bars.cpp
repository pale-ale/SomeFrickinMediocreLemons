#include "Bars.h"
#include "../Player.h"

Bar::Bar(sf::Color BGColor, sf::Color FGColor){
    Background.setSize(sf::Vector2f(barWidth+offset,barHeight+offset));
    Background.setFillColor(sf::Color(BGColor));
    Background.setOrigin(Background.getSize()/2.0f);
    Foreground.setSize(sf::Vector2f(barWidth,barHeight));
    Foreground.setFillColor(sf::Color(FGColor));
    Foreground.setOrigin(Foreground.getSize()/2.0f);
    Foreground.setPosition(Background.getPosition().x+(offset/2),Background.getPosition().y+(offset/2));
}
Bar::Bar(){
    Background.setSize(sf::Vector2f(barWidth+offset,barHeight+offset));
    Background.setFillColor(sf::Color(this->BGColor));
    Background.setOrigin(Background.getSize()/2.0f);
    Foreground.setSize(sf::Vector2f(barWidth,barHeight));
    Foreground.setFillColor(sf::Color(this->FGColor));
    Foreground.setOrigin(Foreground.getSize()/2.0f);
    Foreground.setPosition(Background.getPosition().x+(offset/2),Background.getPosition().y+(offset/2));
}
void Bar::setMax(int newMax){
    this->max = newMax;
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