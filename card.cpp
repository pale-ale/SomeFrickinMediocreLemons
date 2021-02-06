#include "card.h"
#include <memory>
#include "Player.h"

void card::moveGraveyard(){
	graveyard=true;
}
bool card::checkGraveyard(){
	return graveyard;
}
cardType card::getType(){
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
	cardDescription.setPosition(newPosition + descOffset);
}

void card::setRotation(float newRotation){
	Placeable::setRotation(newRotation);
	auto o = sf::Transform().rotate(newRotation).transformPoint(imageOffset);
	auto ot = sf::Transform().rotate(newRotation).transformPoint(descOffset);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + o);
	cardButton.setRotation(newRotation);
	cardDescription.setRotation(newRotation);
	cardDescription.setPosition(getPosition() + ot);
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
	cardImageTexture = std::make_unique<sf::Texture>();
	cardImageTexture->loadFromFile(pathToImage);
	imageSprite.setTexture(*cardImageTexture);
	//does not show font currently neeed to investigate
	if (font->loadFromFile(Settings::defaultFontPath)){
		cardDescription.setString(description);
        cardDescription.setFont(*font);
	    cardDescription.setPosition(getPosition().x,getPosition().y+20);
		cardDescription.setScale(0.17,0.17);
    }else{
        cout << "Error loading font \'" << Settings::defaultFontPath << "\'\n";
    };
}
void card::Play(){
	if (owner){
		owner->playCard(this);
	}
	else{
		cout << "A card was played without an owner.\n";
	}
}