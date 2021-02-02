#pragma once

#include "Settings.h"
#include <list>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ManaType.h"
#include <cmath>
#include "Hand.h"

class card;

using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,0};
    const sf::Vector2f graveyardOffset = {163,-50};
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
};
