#include "card.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"


void Player::drawCards(int count){
    if (deck.size() < count) { cout << "Not enough cards to draw!\n"; throw ;}
    list<card*>::iterator it = deck.end(); advance(it, -count);
    while (it != deck.end()){
        playerhand.addCardToHand(*it);
        (*it)->cardLocation = ECardLocation::hand;
        removeChild(*it);
        (*it)->setFlipState(true);
        it++;
    }
    it = deck.end(); advance(it, -count);
    deck.erase(it, deck.end());
    playerhand.updateHandPositions();
    playerHud.setDeckCount(deck.size());
    playerHud.setHandCount(playerhand.getHand()->size());

}

void Player::playCard(card* cardToPlay){
    playerhand.removeCard(cardToPlay);
    battlefield.AddCard(*cardToPlay);
    cout << "Player " << " played card " << cardToPlay->getName() << endl;
    playerhand.updateHandPositions();
    playerHud.setHandCount(playerhand.getHand()->size());
    if (game){
        game->startTurnOfNextPlayer();
    }else{
        cout << "I need a gameInstance!\n";
    }
}

void Player::addCardToDeck(card *card){
    card->setPosition(transform.getTransform().transformPoint(deckOffset));
    card->setRotation(this->getRotation());
    card->setFlipState(false);
    card->owner = this;
    card->cardLocation = ECardLocation::deck;
    deck.push_back(card);
    playerHud.setDeckCount(deck.size());
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

void Player::addMana(const FMana& m){
	mana = mana + m;
}

void Player::clearMana(){
	this->mana = FMana();
}
	
Player::Player(std::string Name): Player(){
	this->mana=FMana();
	this->name=Name;
}
int Player::getLifePoints(){
    return lifePoints;
}
void Player::setLifePoints(int lifePoints){
    this->lifePoints = lifePoints;
    playerBar.setCurrent(this->lifePoints);
}

Player::Player(){
    battlefield.setPosition(getPosition() + battlefieldOffset);
    battlefield.attachTo(this);
    playerhand.setPosition(getPosition() + handOffset);
    playerhand.attachTo(this);
    playerHud.setPosition(getPosition());
    playerHud.attachTo(this);
    playerBar.setMax(Settings::StartLifePoints);
    playerBar.setPosition(getPosition() + lifePointOffset);
    playerBar.setRotation(90);
    playerBar.attachTo(this);
    playerManaBars.setPosition(getPosition() + manaBarOffset);
    playerManaBars.attachTo(this);
    //playerManaBar
    //addChild(&cardSelector);
}
