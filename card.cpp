#include "card.h"
#include <memory>
#include "Player.h"

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

void card::setPosition(sf::Vector2f newPosition)
{
	Placeable::setPosition(newPosition);
	cardSprite.setPosition(newPosition);
	imageSprite.setPosition(newPosition + imageOffset);
	cardButton.setPosition(newPosition);
}

void card::setRotation(float newRotation){
	Placeable::setRotation(newRotation);
	auto o = sf::Transform().rotate(newRotation).transformPoint(imageOffset);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + o);
	cardButton.setRotation(newRotation);
}

card::card(){
	cardBackTexture.loadFromFile("/usr/share/test/resources/CardBack.png");
	cardFrontTexture.loadFromFile("/usr/share/test/resources/CardFront.png");
	cardSprite.setTexture(cardBackTexture);
	cardSprite.setPosition(getPosition());
	cardSprite.setOrigin(cardDimensions / 2.0f);
	imageSprite.setOrigin(imageDimensions / 2.0f);
	cardButton = Button({getPosition().x, getPosition().y,50,75});
}

void card::updateCardImage(){
	cardImageTexture = std::make_shared<sf::Texture>();
	cardImageTexture->loadFromFile(pathToImage);
	imageSprite.setTexture(*cardImageTexture);
}

void card::Play(){
	if (owner){
		owner->playCard(this);
	}
	else{
		cout << "A card was played without an owner.\n";
	}
}