#pragma once
#include "cardTypes.h"
#include "events/EventCallback.h"
#include <iostream>
#include "IDragAndDroppable.h"
#include "ManaType.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include "ui/Button.h"
#include "ui/MultiSelect.h"
#include "ui/QuickTextBox.h"
#include "actions/DefaultAttack.h"

class Player;

using std::cout;

enum ECardLocation{
	undefined,
	deck,
	hand,
	battlefieldSupport,
	battlefieldBattle,
	battlefieldBattort,
	graveyard
};

class Card : public UIElement, public IDragAndDroppable{
	public:
	Card(UISystem* ui,
		 const string imagePath = "/Unknown.png", 
		 const string desc = "test",
		 const FMana cost = FMana());
	virtual ~Card();
	shared_ptr<Button> cardButton;
	cardType getType();
	void moveGraveyard();
	bool checkGraveyard();
	ECardLocation cardLocation = undefined;
	const string getDescription() const {return description;} 
	const std::shared_ptr<sf::Texture> getTexture() const {return cardImageTexture;}
	void setFlipState(bool frontFaceUp);
	const sf::Vector2f cardDimensions = Settings::cardSize;
	const sf::Vector2f imageDimensions = {40, 40};
	const sf::Vector2f imageOffset = {0, -13};
	const sf::Vector2f descOffset = {-20, 10};
	const sf::Vector2f hpStatOffset = {-20, -40};
	const sf::Vector2f powerStatOffset = {10, -40};
	virtual void setupButtonBinding() = 0;
	virtual void setPosition(const sf::Vector2f &newPosition) override;
	virtual void setRotation(const float &newRotation) override;
	virtual void onCardClicked();
	virtual void onCardBeginMouseover();
	virtual void onCardEndMouseover();
	virtual void OnDragMove(const sf::Vector2f &newPos) override;
	virtual void OnDragStart() override;
	virtual void OnDragEnd() override;
	virtual void onReceiveSelection(list<Card*> cards){cout << "Card: " << name << " received selection\n";};
	virtual void play();
	virtual void tap(){}
	virtual void initializeSubComponents() override;
	virtual void takeDamage(const int& amount);
	virtual void onCardDeath(){cout << "Card: " << name << " received lethal damage.\n";}
    virtual void setSnapPoints(const vector<sf::Vector2f> &points){snapPoints = points;}
	virtual void setOwner(Player *newOwner){owner = newOwner;}
	const vector<shared_ptr<IAction>> getActions() const {return actions;}
	FMana cost;

	protected:
	cardType type;
	string description;
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
	sf::Vector2f scaleVectorSettings(const sf::Vector2f &v){
		return {v.x*Settings::cardScale.x, v.y*Settings::cardScale.y};
	}

	void updateCardImage();
	void updateCardStatDisplay();
	virtual void setupActions(){
		actions.push_back(std::make_shared<DefaultAttack>());
	};
	
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	QuickTextBox cardDescription;
	sf::Text hpStatDisplay;
	sf::Text powerStatDisplay;
	std::shared_ptr<sf::Texture> cardImageTexture;
	shared_ptr<MultiSelect> multiSelector;

	sf::Sprite cardSprite;
	sf::Sprite imageSprite;
	vector<shared_ptr<IAction>> actions;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
		if (multiSelector){
			target.draw(*multiSelector.get());
		}
		if (isVisible){
			UIElement::draw(target, states);
			target.draw(cardSprite, states);
			if (frontFaceUp){
				target.draw(imageSprite, states);
				target.draw(*cardButton, states);
				target.draw(cardDescription, states);
				target.draw(hpStatDisplay, states);
				target.draw(powerStatDisplay, states);
			}
		}
    }
};
