#pragma once

#include "Settings.h"
#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ManaType.h"
#include <cmath>


using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> hand = {};
    list<card*> graveyard = {};
    sf::Vector2f deckOffset = {-190,-90};
    sf::Vector2f handOffset = {0,-50};
    sf::Vector2f graveyardOffset = {300,12};
	FMana mana;
	string name;
	const int circleBegin = 75; 
	const int circleEnd = Settings::defaultWidth - 75;
	float cardspace;
	float rotation;

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
};
