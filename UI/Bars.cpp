#include "Bars.h"
#include "../Player.h"

Bar::Bar(){
    Background.setSize(sf::Vector2f(barWidth+offset,barHeight+offset));
    Background.setFillColor(sf::Color({0,0,0,255}));
    Background.setOrigin(Background.getSize()/2.0f);
    Foreground.setSize(sf::Vector2f(barWidth,barHeight));
    Foreground.setFillColor(sf::Color({255,0,0,255}));
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