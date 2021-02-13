#include "ManaBars.h"

ManaBar::ManaBar() : Bar (){
}
ManaBar::ManaBar(sf::Color bgcolor, sf::Color fgcolor) : Bar (bgcolor,fgcolor){
}
ManaBar::ManaBar(int width, int height, sf::Color bgcolor, sf::Color fgcolor) : Bar (width,height,bgcolor,fgcolor){
}
EManaType ManaBar::getManaType(){
    return this->ManaType;
}
void ManaBar::setPosition(sf::Vector2f newPosition)
{
	Placeable::setPosition(newPosition);
    Background.setPosition(newPosition);
    Foreground.setPosition(newPosition);
}
void ManaBar::setRotation(float newRotation){
    auto delta = transform.getRotation() - newRotation;
    Placeable::setRotation(delta);
	Foreground.setRotation(delta);
    Background.setRotation(delta);
}
ManaBars::ManaBars(unsigned int offset, unsigned int start, unsigned width, unsigned int height){
    int iterator = 0;
    for(ManaBar* i : ManaBarList){
        i->setDimensions(width,height);
        i->setPosition(sf::Vector2f(start+(iterator*offset),height));
        iterator++;
    }
}