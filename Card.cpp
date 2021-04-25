#include <memory>

#include "Battlefield.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"

#include "actions/DefaultAttack.h"

#include "ui/Button.h"
#include "ui/CardPreview.h"
//#include "ui/QuickTextBox.h"


void Card::moveGraveyard()
{
	graveyard = true;
}
bool Card::checkGraveyard()
{
	return graveyard;
}
CardTypes::CardType Card::getType()
{
	return type;
}

void Card::OnDragMove(const sf::Vector2f &newPos)
{
	if (snapPoints.size() > 0)
	{
		auto closestSnapPoint = getClosestPoint<vector<sf::Vector2f>>(newPos, snapPoints, snapPointIndex);
		auto distance = getDistance(newPos, closestSnapPoint);
		if (distance < 25)
		{
			setPosition(closestSnapPoint);
			return;
		}
	}
	snapPointIndex = -1;
	setPosition(newPos);
}

void Card::OnDragStart()
{
	setRotation(0);
	if (owner && owner->bIsMyTurn)
	{
		owner->battlefield->setDrawFreeSpaces(true, true);
		owner->battlefield->setDrawFreeSpaces(true, false);
		setSnapPoints(owner->battlefield->getFreeSnapPoints(true));
	}
	snapPointIndex = -1;
}

void Card::OnDragEnd()
{
	if (owner)
	{
		owner->battlefield->setDrawFreeSpaces(false, true);
		if (snapPointIndex > -1)
		{
			cout << "Card: Requesting to be played on slot " << snapPointIndex << endl;
			owner->playCard(this, snapPointIndex);
		}
		else
		{
			owner->playerhand->updateHandPositions();
		}
	}
}

void Card::setFlipState(bool frontFaceUp)
{
	if (frontFaceUp != this->frontFaceUp)
	{
		cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

void Card::setPosition(const sf::Vector2f &newPosition)
{
	UIElement::setPosition(newPosition);
	cardSprite.setPosition(newPosition);
	imageSprite.setPosition(newPosition + scaleVectorSettings(imageOffset));
	cardButton->setPosition(newPosition);
	cardDescription->setPosition(newPosition + scaleVectorSettings(descOffset));
	hpStatDisplay.setPosition(newPosition + scaleVectorSettings(hpStatOffset));
	powerStatDisplay.setPosition(newPosition + scaleVectorSettings(powerStatOffset));
	cardLabel.setPosition(newPosition + scaleVectorSettings(labelCenterOffset));
}

void Card::setRotation(const float &newRotation)
{
	UIElement::setRotation(newRotation);
	auto t = sf::Transform().rotate(newRotation).scale(Settings::cardScale);
	cardSprite.setRotation(newRotation);
	imageSprite.setRotation(newRotation);
	imageSprite.setPosition(getPosition() + t.transformPoint(imageOffset));
	cardButton->setRotation(newRotation);
	cardDescription->setRotation(newRotation);
	cardDescription->setPosition(getPosition() + t.transformPoint(descOffset));
	hpStatDisplay.setRotation(newRotation);
	hpStatDisplay.setPosition(getPosition() + t.transformPoint(hpStatOffset));
	powerStatDisplay.setRotation(newRotation);
	powerStatDisplay.setPosition(getPosition() + t.transformPoint(powerStatOffset));
	cardLabel.setRotation(newRotation);
	cardLabel.setPosition(getPosition() + t.transformPoint(labelCenterOffset));
}

Card::Card(UISystem *ui, const string imagePath, const string desc, const string title, FMana mana) : UIElement(ui),
																									  pathToImage{string(Settings::programDir) + Settings::relativeAssetCardPath + imagePath},
																									  description{desc},
																									  label{title},
																									  cost{mana},
																									  cardButton{make_shared<Button>(ui, sf::Color{0, 0, 0, 0}, sf::Color{0, 0, 0, 0})},
																									  cardDescription{make_shared<TextBox>(ui)}
{
	cardBackTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardBack);
	cardFrontTexture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardFront);
	cardSprite.setTexture(cardBackTexture);
	cardSprite.setScale(Settings::cardScale);
	cardSprite.setOrigin(Settings::cardSize / 2.0f);
	imageSprite.setScale(Settings::cardScale * 0.0335f);
	imageSprite.setOrigin(imageDimensions / 2.0f);
	updateCardImage();
	cardButton->isDragable = true;
	cardButton->setName(name + "Button");
	cardButton->setScale(Settings::cardScale.x, Settings::cardScale.y);
  	cardButton->onClickCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardEndMouseover);
    cardButton->onDragMoveCallback = std::make_shared<EventCallback<Card, const sf::Vector2f&>>(this, &Card::OnDragMove);
    cardButton->onDragEndCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragEnd);
    cardButton->onDragStartCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragStart);	
	font->loadFromFile(Settings::validFontPath);
	//cardDescription->maxCharacterCountPerLine = 18;
	cardDescription->changeContent(description);
	cardDescription->setScale(Settings::cardScale.x * 0.17, Settings::cardScale.y * 0.17);
	cardDescription->changeSize(Settings::cardSize + descOffset);
	hpStatDisplay.setFont(*font);
	hpStatDisplay.setFillColor(Settings::redColor);
	hpStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
	powerStatDisplay.setFont(*font);
	powerStatDisplay.setFillColor(Settings::blackColor);
	powerStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
	cardLabel.setFont(*font);
	cardLabel.setFillColor(Settings::blackColor);
	cardLabel.setScale(scaleVectorSettings({0.3, 0.3}));
	Placeable::name = "card";
	cardLabel.setString(label);
	cardLabel.setOrigin(sf::Vector2f{cardLabel.getLocalBounds().width, cardLabel.getLocalBounds().height} * .5f);
	updateCardStatDisplay();
}

void Card::updateCardImage()
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

void Card::onCardClicked()
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
	if (cardLocation == battlefieldBattle || cardLocation == battlefieldBattort || cardLocation == battlefieldSupport)
	{
		if (owner->getSelectedCard() == this){
			owner->selectCard(nullptr);
			return;
		}
		owner->selectCard(this);
	}
}

void Card::onCardBeginMouseover()
{
	preview = std::make_shared<CardPreview>(ui, this);
	preview->setPosition({Settings::defaultWidth/2, Settings::defaultHeight/2});
	ui->addToHUDLayer(preview);
}

void Card::onCardEndMouseover()
{
	ui->removeFromHUDLayer(preview.get());
	preview.reset();
}

void Card::initializeSubComponents()
{
	UIElement::initializeSubComponents();
	cardButton->initializeSubComponents();
}

void Card::takeDamage(const int &amount)
{
	health -= amount;
	updateCardStatDisplay();
	if (health <= 0)
	{
		onCardDeath();
	}
}

void Card::play()
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

void Card::updateCardStatDisplay()
{
	hpStatDisplay.setString(to_string(health));
	powerStatDisplay.setString(to_string(power));
}

Card::~Card()
{
	cout << "Card: Destroying card " << name << "...\n";
	ui->removeFromHUDLayer(preview.get());
}

void Card::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isVisible)
	{
		UIElement::draw(target, states);
		target.draw(cardSprite, states);
		if (frontFaceUp)
		{
			target.draw(imageSprite, states);
			target.draw(*cardButton, states);
			target.draw(*cardDescription, states);
			target.draw(hpStatDisplay, states);
			target.draw(powerStatDisplay, states);
			target.draw(cardLabel, states);
		}
	}
}

void Card::setOwner(Player *newOwner){
	for (auto &a : actions){
		a->setOwningPlayer(newOwner);
	}
	owner = newOwner;
}
