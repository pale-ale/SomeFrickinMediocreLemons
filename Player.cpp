#include "Player.h"

void Player::drawCards(int count){
    list<card*>::iterator it = deck.end();
    advance(it, -count);
    hand.insert(hand.begin(), it, deck.end());
    advance(it, -count);
    deck.erase(it, deck.end());
}

void Player::playCard(card * cardToPlay){
    for (int i=0; i<hand.size(); i++){
        list<card*>::iterator playedCard = find(hand.begin(), hand.end(), cardToPlay);
        cout << "Player " << " played card " << cardToPlay->getname() << endl;
        hand.erase(playedCard);
    }
}