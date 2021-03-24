#include "Card.h"
#include <memory>
#include "Player.h"

void card::moveGraveyard()
{
	graveyard = true;
}
bool card::checkGraveyard()
{
	return graveyard;
}
cardType card::getType()
{
	return type;
}
const string card::getName() const
{
	return name;
}

void card::setFlipState(bool frontFaceUp)
{
	if (frontFaceUp != this->frontFaceUp)
	{
		cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

void card::setPosition(sf::Vector2f newPosition)
{
	UIElement::setPosition(newPosition);
	cardSprite.setPosition(newPosition);
	imageSprite.setPosition(newPosition + imageOffset);
	cardButton.setPosition(newPosition);
	cardDescription.setPosition(newPosition + descOffset);
	hpStatDisplay.setPosition(newPosition + powerStatOffset);
	powerStatDisplay.setPosition(newPosition + hpStatOffset);
}

void card::setRotation(float newRotation)
{
	UIElement::setRotation(newRotation);
	auto t = sf::Transform().rotate(newRotation).transformPoint(imageOffset);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + t);
	cardButton.setRotation(newRotation);
	cardDescription.setRotation(newRotation);
	t = sf::Transform().rotate(newRotation).transformPoint(descOffset);
	cardDescription.setPosition(getPosition() + t);
	t = sf::Transform().rotate(newRotation).transformPoint(hpStatOffset);
	hpStatDisplay.setRotation(newRotation);
	hpStatDisplay.setPosition(getPosition() + t);
	t = sf::Transform().rotate(newRotation).transformPoint(powerStatOffset);
	powerStatDisplay.setRotation(newRotation);
	powerStatDisplay.setPosition(getPosition() + t);
}

card::card(UISystem *ui, const string imagePath, const string desc, FMana mana) : 
UIElement(ui), 
pathToImage{string(Settings::programDir) + Settings::relativeAssetCardPath + imagePath},
description{desc}, 
cost{mana},
cardButton{Button(ui, {0, 0, 50, 75})}
{
	cardBackTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardBack);
	cardFrontTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardFront);
	cardSprite.setTexture(cardBackTexture);
	cardSprite.setPosition(getPosition());
	cardSprite.setOrigin(cardDimensions / 2.0f);
	imageSprite.setOrigin(imageDimensions / 2.0f);
	updateCardImage();
	cardButton.setPosition(getPosition());
	font->loadFromFile(Settings::validFontPath);
	cardDescription.setString(description);
	cardDescription.setFont(*font);
	cardDescription.setPosition(getPosition() + descOffset);
	cardDescription.setScale(0.17, 0.17);
	hpStatDisplay.setFont(*font);
	hpStatDisplay.setFillColor(Settings::RedColor);
	hpStatDisplay.setPosition(getPosition() + hpStatOffset);
	hpStatDisplay.setScale(0.5, 0.5);
	powerStatDisplay.setFont(*font);
	powerStatDisplay.setFillColor(Settings::BlackColor);
	powerStatDisplay.setPosition(getPosition() + powerStatOffset);
	powerStatDisplay.setScale(0.5, 0.5);
	Placeable::name = "card";
	updateCardStatDisplay();
}

void card::updateCardImage()
{
	cardImageTexture = std::make_unique<sf::Texture>();
	if (!cardImageTexture->loadFromFile(pathToImage))
	{
		cout << "Card: Error loading image at \'" << pathToImage << "'. Trying the default.\n";
		pathToImage.assign(string(Settings::programDir) + Settings::relativeAssetCardPath + "/Unknown.png");
		cardImageTexture->loadFromFile(pathToImage);
	};
	imageSprite.setTexture(*cardImageTexture);
}

void card::onCardClicked()
{
	if (!owner->bIsMyTurn)
	{
		cout << "Card: Not my turn yet.\n";
		return;
	}
	if (cardLocation == hand)
	{
		if (owner->getMana().canAfford(cost))
		{
			play();
		}
		else
		{
			cout << "Card: Not enough mana to play.\n";
		}
		return;
	}
	if (cardLocation == battlefield)
	{
		tap();
		return;
	}
}

void card::onCardBeginMouseover()
{
	if (owner && owner->bIsMyTurn && !owner->cardSelector->bIsCurrentlySelecting)
	{
		owner->previewCard(this);
	}
}

void card::onCardEndMouseover()
{
	if (owner)
	{
		owner->stopPreviewingCard();
	}
}

void card::takeDamage(const int& amount){
	health -= amount;
	updateCardStatDisplay();
	if (health <= 0){
		onCardDeath();
	}
}

void card::play()
{
	onCardEndMouseover();
	if (owner)
	{
		owner->playCard(this);
		cardButton.OnEndMouseover();
	}
	else
	{
		cout << "Card: I was played without an owner.\n";
	}
}

void card::updateCardStatDisplay(){
	hpStatDisplay.setString(to_string(health));
	powerStatDisplay.setString(to_string(power));
}

card::~card(){
	cout << "Card: Destroying card " << name << "...\n";
	if (owner){
		owner->stopPreviewingCard();
		cout << "Card: Stopped preview\n";
	}
}