#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "cardTypes.h"
#include "UI/Button.h"
#include "Events/EventCallback.h"
#include "ManaType.h"

class Player;

using namespace std;

enum ECardLocation{
	undefined,
	deck,
	hand,
	battlefield,
	graveyard
};

class card : public UIElement{
	public:
	card(const string imagePath = "/usr/share/test/resources/Unknown.png", 
		 const string desc = "test",
		 const FMana cost = FMana());
	Button cardButton;
	cardType getType();
	void moveGraveyard();
	bool checkGraveyard();
	ECardLocation cardLocation = undefined;
	string getName();
	Player* owner = nullptr;
	void setName(const string newName){name=newName;}
	void setFlipState(bool frontFaceUp);
	const sf::Vector2f cardDimensions = {50, 75};
	const sf::Vector2f imageDimensions = {40, 40};
	const sf::Vector2f imageOffset = {0, -13};
	const sf::Vector2f descOffset = {-20, 12};
	virtual void SetupButtonBinding() = 0;
	virtual void setPosition(sf::Vector2f newPosition) override;
	virtual void setRotation(float newRotation) override;
	virtual void OnCardClicked();
	virtual void OnCardBeginMouseover();
	virtual void OnCardEndMouseover();
	virtual void Play();
	FMana cost;

	protected:
	cardType type;
	string name;
	string description;
	int power;
	int health;
	string pathToImage;
	bool frontFaceUp;
	bool graveyard;
	bool tapped;
	std::shared_ptr<sf::Font> font = std::make_unique<sf::Font>();

	void updateCardImage();
	
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	sf::Text cardDescription;
	std::shared_ptr<sf::Texture> cardImageTexture;

	sf::Sprite cardSprite;
	sf::Sprite imageSprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
		if (isVisible){
			target.draw(cardSprite, states);
			if (frontFaceUp){
				target.draw(imageSprite, states);
				target.draw(cardButton, states);
				target.draw(cardDescription, states);
			}
		}
    }
};
