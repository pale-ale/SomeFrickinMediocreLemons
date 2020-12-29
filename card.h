#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cardTypes.h"
using namespace std;

class card : public sf::Drawable{
	public:
	card(cardType Type, string Name, sf::Vector2f Position);
	int getType();
	void moveGraveyard();
	bool checkGraveyard();
	void setPosition(sf::Vector2f newPosition);
	string getName();
	void setFlipState(bool frontFaceUp);
	bool getFlipped();
	virtual bool starteffect(card* card);

	private:
	bool frontFaceUp;
	bool graveyard;
	cardType type;
	string name;
	sf::Vector2f position;
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	sf::Sprite cardSprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {	
        target.draw(cardSprite, states);
    }
};
