#include "Bars.h"
#include "../Player.h"

Bar::Bar(){
    Background.setSize(sf::Vector2f(BarWidth+offset,BarHeight+offset));
    Background.setFillColor(sf::Color({0,0,0,255}));
    HealthBar.setSize(sf::Vector2f(BarWidth,BarHeight));
    HealthBar.setFillColor(sf::Color({255,0,0,255}));
    HealthBar.setPosition(Background.getPosition().x+(offset/2),Background.getPosition().y+(offset/2));
}
void Bar::setLifePointbase(int lifepoints){
    this->LifePointbase = lifepoints;
}
void Bar::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    target.draw(Background);
    target.draw(HealthBar);
}
void Bar::setCurrent(int currentlifepoints){
   HealthBar.setSize(sf::Vector2f((float)BarWidth*std::min((float)(currentlifepoints/(float)this->LifePointbase),1.0f),BarHeight));
}

void Bar::setPosition(sf::Vector2f newPosition)
{
	Placeable::setPosition(newPosition);
    Background.setPosition(newPosition);
    HealthBar.setPosition(Background.getPosition().x+(offset/2),Background.getPosition().y+(offset/2));
}

void Bar::setRotation(float newRotation){
    Placeable::setRotation(newRotation);
	HealthBar.setRotation(((int)newRotation % (180)));
    Background.setRotation(((int)newRotation % (180)));
}