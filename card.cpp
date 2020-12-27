#include "card.h"
void card::moveGraveyard(){
	graveyard=true;
}
bool card::checkGraveyard(){
	return graveyard;
}
string card::getType(){
	return type;
}
string card::getName(){
	return name;
}
card::card (std::string Type, string Name, sf::Vector2<float> Position){
	this->type=Type;
	this->name=Name;
	this->graveyard=false;
	this->position=Position;
	this->cardTexture.loadFromFile("/usr/share/test/resources/CardBack.png");
	this->cardSprite.setTexture(this->cardTexture);
	this->cardSprite.setPosition(this->position);
}
