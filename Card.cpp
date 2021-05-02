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
bool Card::bGetGraveyard()
{
	return graveyard;
}
CardTypes::CardType Card::getType()
{
	return type;
}

void Card::setFlipState(bool frontFaceUp)
{
	if (frontFaceUp != this->frontFaceUp)
	{
		//cardSprite.setTexture(frontFaceUp ? cardFrontTexture : cardBackTexture);
		this->frontFaceUp = frontFaceUp;
	}
}

Card::Card(UISystem *ui, const string imagePath, const string desc, const string title, FMana mana):
	pathToImage{string(Settings::programDir) + Settings::relativeAssetCardPath + imagePath},
	description{desc},
	label{title},
	cost{mana}
{
	if (ui){
		ui = ui;
		cardUI = make_shared<CardUI>(ui, this);
	}
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

void Card::playToIndex(int index){
	owner->battlefield->setDrawFreeSpaces(false, true);
	if (index > -1)
	{
		cout << "Card: Requesting to be played on slot " << index << endl;
		owner->playCard(this, index);
	}
	else
	{
		owner->playerhand->updateHandPositions();
	}
}

bool Card::canAfford(){
	return owner->getMana().canAfford(cost); 
}

Card::~Card()
{
	cout << "Card: Destroying card " << label << "...\n";
}

void Card::setOwner(Player *newOwner)
{
	for (auto &a : actions)
	{
		a->setOwningPlayer(newOwner);
	}
	owner = newOwner;
}
