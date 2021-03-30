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

void card::OnDragMove(const sf::Vector2f &newPos)
{
	if (snapPoints.size() > 0){
		auto closestSnapPoint = getClosestPoint<vector<sf::Vector2f>>(newPos, snapPoints);
		auto distance = getDistance(newPos, closestSnapPoint);
		if (distance < 25){
			setPosition(closestSnapPoint);
			return;
		}
	}
	setPosition(newPos);
}

void card::OnDragStart()
{
	setRotation(0);
	if (owner){
		owner->battlefield->setDrawFreeSpaces(true, true);
		owner->battlefield->setDrawFreeSpaces(true, false);
		setSnapPoints(owner->battlefield->getFreeSnapPoints(true));
	}
}

void card::OnDragEnd()
{
	if(owner){
		owner->battlefield->setDrawFreeSpaces(false, true);
		owner->playCard(this);
	}
}

void card::setFlipState(bool frontFaceUp)
{
	if (frontFaceUp != this->frontFaceUp)
	{
		cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

void card::setPosition(const sf::Vector2f &newPosition)
{
	UIElement::setPosition(newPosition);
	cardSprite.setPosition(newPosition);
	imageSprite.setPosition(newPosition + scaleVectorSettings(imageOffset));
	cardButton->setPosition(newPosition);
	cardDescription.setPosition(newPosition + scaleVectorSettings(descOffset));
	hpStatDisplay.setPosition(newPosition + scaleVectorSettings(hpStatOffset));
	powerStatDisplay.setPosition(newPosition + scaleVectorSettings(powerStatOffset));
}

void card::setRotation(const float &newRotation)
{
	UIElement::setRotation(newRotation);
	auto t = sf::Transform().rotate(newRotation).scale(Settings::cardScale);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + t.transformPoint(imageOffset));
	cardButton->setRotation(newRotation);
	cardDescription.setRotation(newRotation);
	cardDescription.setPosition(getPosition() + t.transformPoint(descOffset));
	hpStatDisplay.setRotation(newRotation);
	hpStatDisplay.setPosition(getPosition() + t.transformPoint(hpStatOffset));
	powerStatDisplay.setRotation(newRotation);
	powerStatDisplay.setPosition(getPosition() + t.transformPoint(powerStatOffset));
}

card::card(UISystem *ui, const string imagePath, const string desc, FMana mana) :
UIElement(ui),
																				  pathToImage{string(Settings::programDir) + Settings::relativeAssetCardPath + imagePath},
																				  description{desc},
																				  cost{mana},
																				  cardButton{std::make_shared<Button>(ui, sf::FloatRect(0, 0, 50, 75))}
{
	cardBackTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardBack);
	cardFrontTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardFront);
	cardSprite.setTexture(cardBackTexture);
	cardSprite.setScale(Settings::cardScale);
	cardSprite.setOrigin(Settings::cardSize / 2.0f);
	imageSprite.setOrigin(imageDimensions / 2.0f);
	imageSprite.setScale(Settings::cardScale);
	updateCardImage();
	cardButton->isDragable = true;
	cardButton->setName(name + "Button");
	cardButton->setSize(scaleVectorSettings(Settings::cardSize));
	font->loadFromFile(Settings::validFontPath);
	cardDescription.setString(description);
	cardDescription.setFont(*font);
	cardDescription.setScale(scaleVectorSettings({0.17, 0.17}));
	hpStatDisplay.setFont(*font);
	hpStatDisplay.setFillColor(Settings::redColor);
	hpStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
	powerStatDisplay.setFont(*font);
	powerStatDisplay.setFillColor(Settings::blackColor);
	powerStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
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

void card::initializeSubComponents()
{
	UIElement::initializeSubComponents();
	cardButton->initializeSubComponents();
}

void card::takeDamage(const int &amount)
{
	health -= amount;
	updateCardStatDisplay();
	if (health <= 0)
	{
		onCardDeath();
	}
}

void card::play()
{
	if (owner)
	{
		owner->playCard(this);
	}
	else
	{
		cout << "Card: I was played without an owner.\n";
	}
}

void card::updateCardStatDisplay()
{
	hpStatDisplay.setString(to_string(health));
	powerStatDisplay.setString(to_string(power));
}

card::~card()
{
	cout << "Card: Destroying card " << name << "...\n";
	if (owner)
	{
		owner->stopPreviewingCard();
		cout << "Card: Stopped preview\n";
	}
}