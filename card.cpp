#include "card.h"
void card::moveGraveyard(){
	graveyard=true;
}
bool card::checkGraveyard(){
	return graveyard;
}
int card::getType(){
	return this->type;
}
string card::getName(){
	return name;
}
card::card (cardType Type, string Name, sf::Vector2f Position){
	this->type=Type;
	this->name=Name;
	this->graveyard=false;
	this->position=Position;
	this->cardBackTexture.loadFromFile("/usr/share/test/resources/CardBack.png");
	this->cardFrontTexture.loadFromFile("/usr/share/test/resources/CardFront.png");
	this->cardSprite.setTexture(this->cardBackTexture);
	this->cardSprite.setPosition(this->position);
}

void card::setFlipState(bool frontFaceUp){
	if (frontFaceUp != this->frontFaceUp){
		this->cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

void card::setPosition(sf::Vector2f newPosition){
	this->position = newPosition;
	this->cardSprite.setPosition(this->position);
}
bool card::starteffect(card* card){
	return true;
}
