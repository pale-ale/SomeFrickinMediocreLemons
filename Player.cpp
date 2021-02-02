#include "Player.h"
#include "Hand.h"
#include "card.h"

void Player::drawCards(int count){
    if (deck.size() < count) { cout << "Not enough cards to draw!\n"; throw ;}
    list<card*>::iterator it = deck.end(); advance(it, -count);
    while (it != deck.end()){
        playerhand.addCardToHand(*it);
        removeChild(*it);
        (*it)->setFlipState(true);
        it++;
    }
    it = deck.end(); advance(it, -count);
    deck.erase(it, deck.end());
    playerhand.updateHandPositions();
}

void Player::playCard(card* cardToPlay){
    playerhand.removeCard(cardToPlay);
    addCardToGraveyard(cardToPlay);
    cout << "Player " << " played card " << cardToPlay->getName() << endl;
    playerhand.updateHandPositions();
}

void Player::addCardToDeck(card *card){
    card->setPosition(this->getPosition() + deckOffset);
    card->setFlipState(false);
    card->owner = this;
    deck.push_back(card);
    addChild(card);
}

void Player::addCardToGraveyard(card* card){
    card->setPosition(this->getPosition() + graveyardOffset);
    card->setFlipState(false);
    card->owner = this;
    graveyard.push_back(card);
    addChild(card);
}

const list<card*>* Player::getHand() const{
    return playerhand.getHand();
}

void Player::printDeck() const{
    auto start = deck.begin();
    auto end = deck.end();
    cout << "Cards in deck:" << endl;
    while (start != end){
        cout << "\t" + (*start)->getName() << endl;
        start++;
    }
}

void Player::printHand() const{
    auto start = playerhand.getHand()->begin();
    auto end = playerhand.getHand()->end();
    cout << "Cards in hand:" << endl;
    while (start != end){
        cout << "\t" + (*start)->getName() << endl;
        start++;
    }
}

void Player::addMana(int Amount, EManaType color){
	mana.add(color, Amount);
}

void Player::clearMana(){
	this->mana = FMana();
}
	
Player::Player(std::string Name){
    Player();
	this->mana=FMana();
	this->name=Name;
}

Player::Player(){
    playerhand.setPosition(getPosition() + handOffset);
    playerhand.attachTo(this);
}
