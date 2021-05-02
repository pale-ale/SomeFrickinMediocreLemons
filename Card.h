#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "CardManagement.h"
#include "ECardLocation.h"
#include "ManaType.h"
#include "Settings.h"

using std::cout;
using std::string;
using std::vector;

class Battlefield;
class CardPreview;
class CardUI;
class IAction;
class Player;

class Card
{
public:
	Card(UISystem *ui = nullptr,
		 const string imagePath = "/Unknown.png",
		 const string desc = "test",
		 const string title = "title",
		 const FMana cost = FMana());
	virtual ~Card();

	CardTypes::CardType getType();
	int getPower() const { return power; }
	bool bGetFlipState() const { return frontFaceUp; }
	bool canAfford();
	const string getDescription() const { return description; }

	void moveGraveyard();
	bool bGetGraveyard();
	void setFlipState(bool frontFaceUp);
	ECardLocation cardLocation = ECardLocation::undefined;

	virtual void play();
	virtual void playToIndex(int i);
	virtual void tap() {}
	virtual void takeDamage(const int &amount);
	virtual void onCardDeath() { cout << "Card: " << label << " received lethal damage.\n"; }
	virtual void setOwner(Player *newOwner);
	void setCardUI(std::shared_ptr<CardUI> newCardUI) { cardUI = newCardUI; }
	std::shared_ptr<CardUI> getCardUI() { return cardUI; }
	Player *getOwner() { return owner; }
	void setHealth(int newHealth) { health = newHealth;	}
	void setMaxHealth(int newMaxHealth)	{ maxHealth = newMaxHealth; }
	int getHealth() const { return health; }
	const vector<std::shared_ptr<IAction>> getActions() const { return actions; }
	FMana cost;
	string pathToImage;
	string label = "DefaultLabel";
	string description = "DefaultDescription";

protected:
	int power = 1;
	int health = 1;
	int maxHealth = 1;
	int defaultMaxHealth = 1;
	bool frontFaceUp = false;
	bool graveyard = false;
	bool tapped = false;
	Player *owner = nullptr;
	std::shared_ptr<CardUI> cardUI = nullptr;
	CardTypes::CardType type;
	vector<std::shared_ptr<IAction>> actions;

	virtual void setupActions() = 0;
};
