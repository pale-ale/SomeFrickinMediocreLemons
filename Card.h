#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "CardManagement.h"
#include "ECardLocation.h"
#include "IDragAndDroppable.h"
#include "ManaType.h"
#include "Settings.h"

#include "ui/TextBox.h"
#include "ui/UIElement.h"


using std::cout;

class Button;
class Battlefield;
class CardPreview;
//class QuickTextBox;
//class TextBox;
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
	std::shared_ptr<Button> cardButton;
	CardTypes::CardType getType();
	int getPower() const{return power;}
	void moveGraveyard();
	bool checkGraveyard();
	ECardLocation cardLocation = undefined;
	const string getDescription() const {return description;} 
	const std::shared_ptr<sf::Texture> getTexture() const {return cardImageTexture;}
	void setFlipState(bool frontFaceUp);
	const sf::Vector2f cardDimensions = Settings::cardSize;
	const sf::Vector2f imageDimensions = {1200, 900};
	const sf::Vector2f imageOffset = {0, -13};
	const sf::Vector2f descOffset = {-20, 10};
	const sf::Vector2f labelCenterOffset = {0, -35};
	const sf::Vector2f hpStatOffset = {-20, -40};
	const sf::Vector2f powerStatOffset = {10, -40};
	virtual void setPosition(const sf::Vector2f &newPosition) override;
	virtual void setRotation(const float &newRotation) override;
	virtual void onCardClicked();
	virtual void onCardBeginMouseover();
	virtual void onCardEndMouseover();
	virtual void OnDragMove(const sf::Vector2f &newPos) override;
	virtual void OnDragStart() override;
	virtual void OnDragEnd() override;
	virtual void play();
	virtual void tap(){}
	virtual void initializeSubComponents() override;
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

	protected:
	CardTypes::CardType type;
	string description = "DefaultDescription";
	string label = "DefaultLabel";
	string pathToImage;
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
	std::shared_ptr<sf::Font> font = std::make_unique<sf::Font>();
	std::shared_ptr<CardPreview> preview = nullptr;
	sf::Vector2f scaleVectorSettings(const sf::Vector2f &v){
		return {v.x*Settings::cardScale.x, v.y*Settings::cardScale.y};
	}
	void updateCardImage();
	void updateCardStatDisplay();
	virtual void setupActions() = 0;
	
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	std::shared_ptr<TextBox> cardDescription;
	sf::Text hpStatDisplay;
	sf::Text powerStatDisplay;
	sf::Text cardLabel;
	std::shared_ptr<sf::Texture> cardImageTexture;

	sf::Sprite cardSprite;
	sf::Sprite imageSprite;
	vector<std::shared_ptr<IAction>> actions;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
