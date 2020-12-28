#pragma once

#include <list>
#include "card.h"
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ManaType.h"

using namespace std;

class Player: public sf::Drawable{
    private:
    list<card*> deck = {};
    list<card*> hand = {};
    list<card*> graveyard = {};
	FMana mana;
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
	void addMana(int amount, EManaType color);
    const FMana getMana(){return mana;}
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
