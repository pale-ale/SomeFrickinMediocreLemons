#include <memory>
#include "card.h"

void card::moveGraveyard(){
	graveyard=true;
}
bool card::checkGraveyard(){
	return graveyard;
}
int card::getType(){
	return type;
}
string card::getName(){
	return name;
}

void card::setFlipState(bool frontFaceUp){
	if (frontFaceUp != this->frontFaceUp){
		cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

void card::SetPosition(sf::Vector2f newPosition){
	position = newPosition;
	cardSprite.setPosition(position);
	imageSprite.setPosition(position + sf::Vector2f(5, 4));
	cardButton.SetPosition(position);
}

void card::SetRotation(float newRotation){
	rotation = newRotation;
	cardSprite.setRotation(rotation);
	imageSprite.setRotation(rotation);
	cardButton.SetRotation(rotation);
}

card::card(){
	cardBackTexture.loadFromFile("/usr/share/test/resources/CardBack.png");
	cardFrontTexture.loadFromFile("/usr/share/test/resources/CardFront.png");
	cardSprite.setTexture(cardBackTexture);
	cardSprite.setPosition(position);
	cardButton = Button({position.x, position.y,50,75});
}

void card::updateCardImage(){
	cardImageTexture = std::make_shared<sf::Texture>();
	cardImageTexture->loadFromFile(pathToImage);
	imageSprite.setTexture(*cardImageTexture);
}

void card::Play(){
	cout << "Like a fiddle!\n";
}