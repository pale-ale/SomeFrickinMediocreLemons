#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "cardTypes.h"
#include "UI/Button.h"

using namespace std;

class card : public sf::Drawable{
	public:
	card();
	Button cardButton;
	int getType();
	void moveGraveyard();
	bool checkGraveyard();
	void setPosition(sf::Vector2f newPosition);
	string getName();
	void setFlipState(bool frontFaceUp);
	bool getFlipped();

	protected:
	cardType type;
	string name;
	string description;
	int power;
	int health;
	string pathToImage = "/usr/share/test/resources/fireball.png";
	
	bool frontFaceUp;
	bool graveyard;

	void updateCardImage();
	
	sf::Vector2f position;

	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	std::shared_ptr<sf::Texture> cardImageTexture;

	sf::Sprite cardSprite;
	sf::Sprite imageSprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {	
        target.draw(cardSprite, states);
		target.draw(imageSprite, states);
    }
};
