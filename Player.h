#pragma once

#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ManaType.h"


using namespace std;

class Player: public UIElement{
    private:
    list<card*> deck = {};
    list<card*> hand = {};
    list<card*> graveyard = {};
    sf::Vector2f deckPosition = {12,12};
    sf::Vector2f handPosition = {100,12};
    sf::Vector2f graveyardPosition = {300,12};
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
};
