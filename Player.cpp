#include "Player.h"
#include "Hand.h"

void Player::drawCards(int count){
    if (deck.size() < count) { cout << "Not enough cards to draw!\n"; throw ;}
    list<card*>::iterator it = deck.end(); advance(it, -count);
    while (it != deck.end()){
        Playerhand.addHand(*it);
        (*it)->setFlipState(true);
        it++;
    }
    //hand.insert(hand.begin(), it, deck.end());
    //Playerhand.addHand((*it));
    it = deck.end(); advance(it, -count);
    deck.erase(it, deck.end());
    Playerhand.drawHand(this->position);
}

void Player::playCard(card* cardToPlay){
    for (int i=0; i<(*Playerhand.getHand()).size(); i++){
        Playerhand.removeCard(cardToPlay);
        cout << "Player " << " played card " << cardToPlay->getName() << endl;
    }
    Playerhand.drawHand(this->position);
}

void Player::addCardToDeck(card *card){
    card->SetPosition(this->position + deckOffset);
    card->setFlipState(false);
    deck.push_back(card);
    addChild(card);
}

const list<card*>* Player::getHand(){
    return Playerhand.getHand();
}

void Player::printDeck(){
    auto start = deck.begin();
    auto end = deck.end();
    cout << "Cards in deck:" << endl;
    while (start != end){
        cout << "\t" + (*start)->getName() << endl;
        start++;
    }
}

void Player::printHand(){
    auto start = (*Playerhand.getHand()).begin();
    auto end = (*Playerhand.getHand()).end();
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
	this->mana=FMana();
	this->name=Name;
}
