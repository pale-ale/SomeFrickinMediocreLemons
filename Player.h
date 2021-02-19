#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Battlefield.h"
#include "Hand.h"
#include "ManaType.h"
#include "UI/PlayerHUD.h"
#include "Settings.h"
#include "UI/Bar.h"
#include "UI/CardSelector.h"
#include "UI/ManaBars.h"


class card;
class Game;

using std::shared_ptr;
using namespace std;

class Player: public UIElement{
    private:
    list<shared_ptr<card>> deck = {};
    list<shared_ptr<card>> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,50};
    const sf::Vector2f lifePointOffset = {125,-30};
    const sf::Vector2f manaBarOffset = {-132, -35};
    const sf::Vector2f graveyardOffset = {163,-50};
    const sf::Vector2f battlefieldOffset = {0,-125};
	FMana mana;
	string name;	
    Game* game = nullptr;
    int lifePoints=Settings::StartLifePoints;

    public:
	Player(UISystem* ui, string name);
	Player(UISystem* ui);
    void setGame(Game* newGame){game = newGame;};
    Game* getGame(){return game;};
    void drawCards(const int count);
    void playCard(card* card);
    void previewCard(const card& cardToPreview);
    void stopPreviewingCard();
    void cardSelectionUpdated(){
        if (awaitingSelection){
            awaitingSelection->tap();
        }
        cardSelector.resetSelection();
    };
    card* awaitingSelection = nullptr;
    void addCardToDeck(shared_ptr<card> card);
    void addCardToGraveyard(shared_ptr<card> card);
    const list<shared_ptr<card>> getHand() const;
    void printDeck() const;
    void printHand() const;
	void addMana(int amount, EManaType color);
	void addMana(const FMana& m);
    const FMana getMana() const {return mana;}
	void clearMana();
    string getName(){return name;}
    bool bIsMyTurn;
    bool isSelectingCards;
    void startSelection(bool battlefield=true, bool enemy=true);
    Hand playerhand;
    Battlefield battlefield;
    PlayerHUD playerHud;
    Bar playerBar;
    ManaBars playerManaBars;
    CardSelector cardSelector;
    int getLifePoints();
    void setLifePoints(int);
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        target.draw(playerHud); //this is drawn twice. not an issue right now though.
    }
};
