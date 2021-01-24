#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "cardTypes.h"
#include "UI/Button.h"
#include "Events/EventCallback.h"


using namespace std;

class card : public UIElement{
	public:
	card();
	Button cardButton;
	int getType();
	void moveGraveyard();
	bool checkGraveyard();
	string getName();
	void setName(const string newName){name=newName;}
	void setFlipState(bool frontFaceUp);
	const sf::Vector2f cardDimensions = {50, 75};
	const sf::Vector2f imageDimensions = {40, 40};
	const sf::Vector2f imageOffset = {0, 13};
	virtual void SetupButtonBinding() = 0;
	virtual void SetPosition(sf::Vector2f newPosition) override;
	virtual void SetRotation(float newRotation) override;
	virtual bool OnMouseButtonDown() override {cout << "test\n"; return true;};
	virtual void Play();

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
	
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	std::shared_ptr<sf::Texture> cardImageTexture;

	sf::Sprite cardSprite;
	sf::Sprite imageSprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {	
		if (isVisible){
			target.draw(cardSprite, states);
			if (frontFaceUp)
				target.draw(imageSprite, states);
				target.draw(cardButton, states);
		}
    }
};
