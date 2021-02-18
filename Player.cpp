#include "card.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"


void Player::drawCards(int count){

    if (deck.size() < count) { cout << "Not enough cards to draw!\n"; throw ;}

    auto it = deck.rbegin();
    shared_ptr<card> card;
   
    for (int i = 0; i < count; i++){
        card = *it; //how does this work without changing it?? does it get moved when resized with pop?
        deck.pop_back();
        playerhand.addCardToHand(card);
        card->cardLocation = ECardLocation::hand;
        card->setFlipState(true);
    }
    
    playerhand.updateHandPositions();
    playerHud.setDeckCount(deck.size());
    playerHud.setHandCount(playerhand.getHand().size());
}

void Player::playCard(shared_ptr<card> cardToPlay){
    playerhand.removeCard(cardToPlay);
    mana-=cardToPlay->cost;
    playerManaBars.updateManaBars(&mana);
    battlefield.addCard(cardToPlay);
    cout << "Player " << " played card " << cardToPlay->getName() << endl;
    playerhand.updateHandPositions();
    playerHud.setHandCount(playerhand.getHand().size());
    if (game){
        game->startTurnOfNextPlayer();
    }else{
        cout << "I need a gameInstance!\n";
    }
}

void Player::addCardToDeck(shared_ptr<card> card){
    card->setPosition(transform.getTransform().transformPoint(deckOffset));
    card->setRotation(this->getRotation());
    card->setFlipState(false);
    card->owner = this;
    card->cardLocation = ECardLocation::deck;
    deck.push_back(card);
    playerHud.setDeckCount(deck.size());
    addChild(card.get());
}

void Player::addCardToGraveyard(shared_ptr<card> card){
    card->setPosition(this->getPosition() + graveyardOffset);
    card->setFlipState(false);
    card->owner = this;
    graveyard.push_back(card);
    addChild(card.get());
}

const list<shared_ptr<card>> Player::getHand() const{
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
    auto hand = playerhand.getHand();
    auto start = hand.begin();
    auto end = hand.end();
    cout << "Cards in hand: " << hand.size() << endl;
    while (start != end){
        cout << "\t" + (*start)->getName() << endl;
        start++;
    }
}

void Player::addMana(int Amount, EManaType color){
	mana.add(color, Amount);
    playerManaBars.updateManaBars(&mana);
}

void Player::addMana(const FMana& m){
	mana = mana + m;
    playerManaBars.updateManaBars(&mana);
}

void Player::clearMana(){
	this->mana = FMana();
    playerManaBars.updateManaBars(&mana);
}
	
Player::Player(UISystem* ui, std::string Name): 
Player(ui){
	this->mana=FMana();
	this->name=Name;
}
int Player::getLifePoints(){
    return lifePoints;
}
void Player::setLifePoints(int lifePoints){
    this->lifePoints = lifePoints;
    playerBar.setFillFactor((float)this->lifePoints / Settings::StartLifePoints);
}

Player::Player(UISystem* ui):
UIElement(ui), 
playerhand{Hand(ui)},
battlefield{Battlefield(ui)},
playerBar{Bar(ui)},
cardSelector{CardSelector(ui)},
playerManaBars{ManaBars(ui,50,25)},
playerHud{PlayerHUD(ui)}
{
    battlefield.setPosition(getPosition() + battlefieldOffset);
    battlefield.attachTo(this);
    playerhand.setPosition(getPosition() + handOffset);
    playerhand.attachTo(this);
    playerHud.setPosition(getPosition());
    playerHud.attachTo(this);
    playerBar.setPosition(getPosition() + lifePointOffset);
    playerBar.setRotation(90);
    playerBar.attachTo(this);
    playerBar.setFillFactor((float)lifePoints / Settings::StartLifePoints);
    playerManaBars.setPosition(getPosition() + manaBarOffset);
    playerManaBars.setRotation(-90);
    playerManaBars.attachTo(this);
    addChild(&cardSelector);
}

void Player::startSelection(bool battlefield, bool enemy){
    Player* p = enemy ? game->getNextTurnPlayer() : this;
    cardSelector.bIsCurrentlySelecting = true;
    cout << "selstate: " << cardSelector.bIsCurrentlySelecting << endl;
    if (battlefield){
        cardSelector.setSelectionTarget(p->battlefield.getCards(), false);
    }
}

void Player::previewCard(const card& cardToPreview){
    if (!cardSelector.bIsCurrentlySelecting)
    {
        playerHud.generatePreview(cardToPreview);
    }
}

void Player::stopPreviewingCard(){
    playerHud.removePreview();
}
