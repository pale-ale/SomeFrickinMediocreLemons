#include "Hand.h"
#include <cmath>

void Hand::drawHand(sf::Vector2f position){
    auto start = hand.begin();
    auto end = hand.end();
	//calculated for space per card
    int handwidth = 200;
	float slotWidth = (handwidth/(float)hand.size());
	int currentSlotNumber = 0;
    int leftHandBoundary = position.x + handOffset.x - handwidth/2;
    int leftmostRotation = -30;
    float rotationStep = abs(leftmostRotation)/float(hand.size());
	while(start != end) {
        auto x = slotWidth*currentSlotNumber - slotWidth*(hand.size()/2);
        auto y = -0.003*pow((x),2)+20;
		rotation=(rotationStep * (currentSlotNumber - (int)hand.size()/2));
		(*start)->SetPosition(sf::Vector2f(position.x + handOffset.x + x, position.y + handOffset.y - y));
		(*start)->SetRotation(rotation);
		start++;
        currentSlotNumber++;
	}
}
const list <card*>* Hand::getHand(){
    return &hand;
}
bool Hand::addHand(card* cardtoadd){
    if(hand.size()<maxHandsize){
        hand.push_back(cardtoadd);
        return true;
    }
    else{
        return false;
    }
}
bool Hand::removeCard(card* cardtoremove){
    list<card*>::iterator playedCard = find(hand.begin(), hand.end(), cardtoremove);
    hand.erase(playedCard);
}
