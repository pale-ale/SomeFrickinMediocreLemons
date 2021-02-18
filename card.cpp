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
}

void card::setRotation(float newRotation)
{
	UIElement::setRotation(newRotation);
	auto o = sf::Transform().rotate(newRotation).transformPoint(imageOffset);
	auto ot = sf::Transform().rotate(newRotation).transformPoint(descOffset);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + o);
	cardButton.setRotation(newRotation);
	cardDescription.setRotation(newRotation);
	cardDescription.setPosition(getPosition() + ot);
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
	//cardButton.setSize({50,75});
	font->loadFromFile(Settings::validFontPath);
	cardDescription.setString(description);
	cardDescription.setFont(*font);
	cardDescription.setPosition(getPosition().x, getPosition().y + 20);
	cardDescription.setScale(0.17, 0.17);
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
		owner->playCard(shared_from_this());
	}
	else
	{
		cout << "A card was played without an owner.\n";
	}
}
