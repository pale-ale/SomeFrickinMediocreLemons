#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "CardManagement.h"
#include "ECardLocation.h"
#include "IDragAndDroppable.h"
#include "ManaType.h"
#include "Settings.h"

#include "ui/UIElement.h"

using std::cout;

class Battlefield;
class CardPreview;
class IAction;
class Player;

class Card : public UIElement, public IDragAndDroppable{
	public:
	Card(UISystem* ui,
		 const string imagePath = "/Unknown.png", 
		 const string desc = "test",
		 const string title = "title",
		 const FMana cost = FMana());
	virtual ~Card();
	CardTypes::CardType getType();
	int getPower() const{return power;}
	bool getFlipState() const{return frontFaceUp;}
	void moveGraveyard();
	bool checkGraveyard();
	ECardLocation cardLocation = undefined;
	const string getDescription() const {return description;} 
	void setFlipState(bool frontFaceUp);
	const sf::Vector2f cardDimensions = Settings::cardSize;
	
	virtual void onCardClicked();
	virtual void onCardBeginMouseover();
	virtual void onCardEndMouseover();
	virtual void OnDragMove(const sf::Vector2f &newPos) override;
	virtual void OnDragStart() override;
	virtual void OnDragEnd() override;
	virtual void play();
	virtual void tap(){}
	virtual void takeDamage(const int& amount);
	virtual void onCardDeath(){cout << "Card: " << name << " received lethal damage.\n";}
    virtual void setSnapPoints(const vector<sf::Vector2f> &points){snapPoints = points;}
	virtual void setOwner(Player *newOwner);
	void setHealth(int newHealth){
		health = newHealth;
	}
	void setMaxHealth(int newMaxHealth){
		maxHealth = newMaxHealth;
	}
	int getHealth() const {return health;}
	const vector<std::shared_ptr<IAction>> getActions() const {return actions;}
	FMana cost;
	string pathToImage;
	string label = "DefaultLabel";
	string description = "DefaultDescription";
	protected:
	CardTypes::CardType type;
	vector<sf::Vector2f> snapPoints;
	int power = 1;
	int health = 1;
	int maxHealth = 1;
	int defaultMaxHealth = 1;
	int snapPointIndex = -1;
	bool frontFaceUp = false;
	bool graveyard = false;
	bool tapped = false;
	Player* owner = nullptr;
	std::shared_ptr<CardPreview> preview = nullptr;
	sf::Vector2f scaleVectorSettings(const sf::Vector2f &v){
		return {v.x*Settings::cardScale.x, v.y*Settings::cardScale.y};
	}
	virtual void setupActions() = 0;
	
	vector<std::shared_ptr<IAction>> actions;
};
