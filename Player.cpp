#include "Player.h"

void Player::drawCards(int count){
    if (deck.size() < count) { cout << "Not enough cards to draw!\n"; throw ;}
    list<card*>::iterator it = deck.end(); advance(it, -count);
    while (it != deck.end()){
        hand.push_back(*it);
        (*it)->setFlipState(true);
        (*it)->SetPosition(handPosition);
        it++;
    }
    hand.insert(hand.begin(), it, deck.end());
    it = deck.end(); advance(it, -count);
    deck.erase(it, deck.end());
	printHand();
}

void Player::playCard(card* cardToPlay){
    for (int i=0; i<hand.size(); i++){
        list<card*>::iterator playedCard = find(hand.begin(), hand.end(), cardToPlay);
        cout << "Player " << " played card " << cardToPlay->getName() << endl;
        hand.erase(playedCard);
    }
}

void Player::addCardToDeck(card *card){
    card->SetPosition(deckPosition);
    card->setFlipState(false);
    deck.push_back(card);
    addChild(card);
}

const list<card*>* Player::getHand(){
    return &hand;
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
    auto start = hand.begin();
    auto end = hand.end();
	//calculated for space per card
	float cardspace = ((circleEnd-circleBegin)/(float)hand.size());
	int cardspaceiteration = circleBegin + cardspace;
	while(start != end) {
		rotation=((cardspaceiteration/(float)(circleEnd-circleBegin)*180));
		//complete trash at this point
		cout << rotation << endl;
		height=(float)(((circleEnd-circleBegin)/2)+cardspaceiteration)-300;
		cout << height << endl;
		(*start)->SetPosition(sf::Vector2f(cardspaceiteration,height));
		(*start)->SetRotation(rotation);
		cardspaceiteration=cardspaceiteration+cardspace;
		start++;
	}
	
    /*cout << "Cards in hand:" << endl;
    while (start != end){
        cout << "\t" + (*start)->getName() << endl;
        start++;
    }
*/
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
