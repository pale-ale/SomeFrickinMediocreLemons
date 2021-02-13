#include "ManaBars.h"

/*ManaBar::ManaBar() : Bar (){}
ManaBar::ManaBar(sf::Color bgcolor, sf::Color fgcolor) : Bar (bgcolor,fgcolor){}
ManaBar::ManaBar(int width, int height, sf::Color bgcolor, sf::Color fgcolor) : Bar (width,height,bgcolor,fgcolor){}
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
}*/

//still needs updates
ManaBars::ManaBars(const int offset, const unsigned int width, const unsigned int height){
    int y = 0;
    this->offset=offset;
    for(Bar* i : ManaBarList){
        i->setDimensions(width,height);
        i->setPosition(sf::Vector2f(0,(y*offset)));
        y++;
        cout << "drawing Bar" <<endl;
    }
}

void ManaBars::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    for(Bar* i : ManaBarList){
    target.draw(*i);
    }
}
void ManaBars::setPosition(sf::Vector2f newPosition) {
    int y = 0;
    for(Bar* i : ManaBarList){
        i->setPosition(sf::Vector2f(newPosition.x,newPosition.y+y*offset));
        y++;
    }
}
void ManaBars::updateManaBars(FMana* Fmana){
    for(Bar* i : ManaBarList){
        if (i->getFGColor()==Settings::BlackColor)
        i->setCurrent(Fmana->Black);
        if (i->getFGColor()==Settings::BlueColor)
        i->setCurrent(Fmana->Blue);
        if (i->getFGColor()==Settings::GreenColor)
        i->setCurrent(Fmana->Green);
        if (i->getFGColor()==Settings::RedColor)
        i->setCurrent(Fmana->Red);
        if (i->getFGColor()==Settings::WhiteColor)
        i->setCurrent(Fmana->White);
    }
}