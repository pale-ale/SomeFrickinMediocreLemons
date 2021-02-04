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

class card;

using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,50};
    const sf::Vector2f graveyardOffset = {163,-50};
    const sf::Vector2f battlefieldOffset = {0,-125};
	FMana mana;
	string name;	

    public:
	Player(string name);
	Player();
    void drawCards(const int count);
    void playCard(card* card);
    void addCardToDeck(card *card);
    void addCardToGraveyard(card* card);
    const list<card*>* getHand() const;
    void printDeck() const;
    void printHand() const;
	void addMana(int amount, EManaType color);
    const FMana getMana() const {return mana;}
	void clearMana();
    Hand playerhand;
    Battlefield battlefield;
    PlayerHUD playerHud;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        target.draw(playerHud); //this is drawn twice. not an issue right now though.
    }
};
