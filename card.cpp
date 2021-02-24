#include "card.h"
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
UIElement(ui), pathToImage{imagePath}, description{desc}, cost{mana}, cardButton{Button(ui, {0, 0, 50, 75})}
{
	cardBackTexture.loadFromFile("/usr/share/test/resources/CardBack.png");
	cardFrontTexture.loadFromFile("/usr/share/test/resources/CardFront.png");
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
	updateCardStatDisplay();
}

void card::updateCardImage()
{
	cardImageTexture = std::make_unique<sf::Texture>();
	if (!cardImageTexture->loadFromFile(pathToImage))
	{
		//cout << "Error loading \'" << pathToImage << "'. Resetting to default.\n";
		pathToImage = "/usr/share/test/resources/Unknown.png";
		cardImageTexture->loadFromFile(pathToImage);
	};
	imageSprite.setTexture(*cardImageTexture);
}

void card::onCardClicked()
{
	if (!owner->bIsMyTurn)
	{
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
			cout << "Not enough mana to play.\n";
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
	cardButton.setColor({255, 255, 255, 100});
	if (owner && !owner->isSelectingCards)
	{
		owner->previewCard(*this);
	}
}

void card::onCardEndMouseover()
{
	cardButton.setColor({100, 100, 100, 0});
	if (owner)
	{
		owner->stopPreviewingCard();
	}
}

void card::play()
{
	onCardEndMouseover();
	if (owner)
	{
		owner->playCard(this);
	}
	else
	{
		cout << "A card was played without an owner.\n";
	}
}

void card::updateCardStatDisplay(){
	hpStatDisplay.setString(to_string(health));
	powerStatDisplay.setString(to_string(power));
}

card::~card(){
	cout << "Destroying card " << name << "!\n";
	ui->removeListener(&cardButton);
	owner->stopPreviewingCard();
}