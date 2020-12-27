#pragma once

#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Player: public sf::Drawable{
    private:
    list<card*> deck = {};
    list<card*> hand = {};
    list<card*> graveyard = {};
	int mana;
	string name;

    public:
	Player(string name);
	Player();
    void drawCards(const int count);
    void playCard(card* card);
    const list<card*>* getHand();
    void addCardToDeck(card &card);
    void printDeck();
    void printHand();
	void addMana(int);
	void removeMana(int);
	void clearMana();

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        auto cardIterator = hand.begin();
        while (cardIterator != hand.end()){
            target.draw(**cardIterator);
            cardIterator++;
        }
    }
};
