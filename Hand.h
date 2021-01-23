#pragma once
#include <SFML/Graphics.hpp>
#include "card.h"

class Hand{
private:
const int handwidth=200;
float slotWidth;
int currentslotNumber = 0;
int leftHandBoundary;
int leftmostRotation = -30;
float rotationStep;
float cardspace;
float rotation;
const int maxHandsize = 10;
list<card*> hand = {};
const sf::Vector2f handOffset = {0,-50};

public:
void drawHand(sf::Vector2f position);
const list<card*>* getHand();
bool addHand(card * cardtoadd);
bool insertHand(list<card*>::iterator it);
bool removeCard(card* cardtoremove);
};