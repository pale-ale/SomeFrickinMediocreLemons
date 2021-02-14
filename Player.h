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


using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> graveyard = {};
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
	Player(string name);
	Player();
    void setGame(Game* newGame){game = newGame;};
    Game* getGame(){return game;};
    void drawCards(const int count);
    void playCard(card* card);
    void addCardToDeck(card *card);
    void addCardToGraveyard(card* card);
    const list<card*>* getHand() const;
    void printDeck() const;
    void printHand() const;
	void addMana(int amount, EManaType color);
	void addMana(const FMana& m);
    const FMana getMana() const {return mana;}
	void clearMana();
    string getName(){return name;}
    bool bIsMyTurn = false;
    Hand playerhand;
    Battlefield battlefield;
    PlayerHUD playerHud;
    Bar playerBar;
    ManaBars playerManaBars = ManaBars(50,25);
    CardSelector cardSelector;
    int getLifePoints();
    void setLifePoints(int);
    
    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        target.draw(playerHud); //this is drawn twice. not an issue right now though.
    }
};
