#include <memory>

#include "Battlefield.h"
#include "Card.h"
#include "Hand.h"
#include "Player.h"

#include "actions/DefaultAttack.h"

#include "ui/CardPreview.h"

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
		//cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

Card::Card(UISystem *ui, const string imagePath, const string desc, const string title, FMana mana) : UIElement(ui),
																									  pathToImage{string(Settings::programDir) + Settings::relativeAssetCardPath + imagePath},
																									  description{desc},
																									  label{title},
																									  cost{mana}
{	
	Placeable::name = "card";
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

void Card::takeDamage(const int &amount)
{
	health -= amount;
	//updateCardStatDisplay();
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


Card::~Card()
{
	cout << "Card: Destroying card " << name << "...\n";
	ui->removeFromHUDLayer(preview.get());
}

void Card::setOwner(Player *newOwner){
	for (auto &a : actions){
		a->setOwningPlayer(newOwner);
	}
	owner = newOwner;
}
