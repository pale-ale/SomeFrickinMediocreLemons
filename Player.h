#pragma once

#include "Settings.h"
#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ManaType.h"
#include <cmath>
#include "Hand.h"


using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> graveyard = {};
    const sf::Vector2f deckOffset = {-163,-50};
    const sf::Vector2f handOffset = {0,-50};
    const sf::Vector2f graveyardOffset = {300,12};
	FMana mana;
	string name;
	

    public:
	Player(string name);
	Player() {}
    void drawCards(const int count);
    void playCard(card* card);
    const list<card*>* getHand();
    void addCardToDeck(card *card);
    void printDeck();
    void printHand();
	void addMana(int amount, EManaType color);
    const FMana getMana(){return mana;}
	void clearMana();
    Hand Playerhand;
};
