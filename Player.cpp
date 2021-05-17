#include "Battlefield.h"
#include "Card.h"
#include "Game.h"
#include "Hand.h"
#include "IAction.h"
#include "Player.h"

#include "cards/PlayerCard.h"

#include "ui/CardSelector.h"

/*
Lets the player draw count cards from his deck.
Throws an error if not enough cards are present.
*/
void Player::drawCards(int count)
{
    if (deck.size() < count)
    {
        cout << "Player: Not enough cards to draw!\n";
        throw;
    }

    for (int i = 0; i < count; ++i)
    {
        auto c = removeCardFromDeckTop();
        playerhand->addCardToHand(c);
    }
    playerhand->updateHandPositions();
    playerHud->setDeckCount(deck.size());
    playerHud->setHandCount(playerhand->getHandData().size());
}

/*
Makes player play the card cardToPlay to the slot slot on the battlefield.
Ends the player's turn.
*/
void Player::playCard(Card *cardToPlay, int slot)
{
    auto sharedCardPtr = playerhand->removeCard(cardToPlay);
    mana -= cardToPlay->cost;
    playerManaBars->updateManaBars(&mana);
    battlefield->addCard(sharedCardPtr, true, slot);
    cout << "Player: " << name << " played card " << cardToPlay->label << endl;
    playerhand->updateHandPositions();
    playerHud->setHandCount(playerhand->getHandData().size());
    if (game)
    {
        game->startTurnOfNextPlayer();
    }
    else
    {
        cout << "Player: I need a gameInstance!\n";
    }
}

/*Adds a card to the end of the player's deck.*/
void Player::addCardToDeck(shared_ptr<Card> card)
{
    auto cardUI = card->getCardUI();
    cardUI->setPosition(transform.getTransform().transformPoint(deckOffset));
    cardUI->setRotation(this->getRotation());
    card->setFlipState(false);
    card->setOwner(this);
    card->cardLocation = ECardLocation::deck;
    deck.push_back(card);
    playerHud->setDeckCount(deck.size());
    //addChild(card);
}

/*Adds a card to the player's graveyard's back.*/
void Player::addCardToGraveyard(shared_ptr<Card> card)
{

    card->getCardUI()->setPosition(this->getPosition() + graveyardOffset);
    card->setFlipState(false);
    card->setOwner(this);
    graveyard.push_back(card);
    //addChild(card);
}

const list<Card *> Player::getHand() const
{
    return playerhand->getHandData();
}

void Player::printDeck() const
{
    cout << "Player: Cards in deck:" << deck.size() << endl;
    for (auto &c : deck)
    {
        cout << "\t" + c->label << endl;
    }
}

void Player::printHand() const
{
    auto hand = playerhand->getHandData();
    cout << "Player: Cards in hand: " << hand.size() << endl;
    for (auto &c : hand)
    {
        cout << "\t" + c->label << endl;
    }
}

void Player::addMana(int Amount, EManaType color)
{
    mana.add(color, Amount);
    playerManaBars->updateManaBars(&mana);
}

void Player::addMana(const FMana &m)
{
    mana = mana + m;
    playerManaBars->updateManaBars(&mana);
}

void Player::clearMana()
{
    this->mana = FMana();
    playerManaBars->updateManaBars(&mana);
}

int Player::getLifePoints()
{
    return lifePoints;
}

void Player::setLifePoints(int lifePoints)
{
    this->lifePoints = lifePoints;
    playerBar->setFillFactor((float)this->lifePoints / Settings::StartLifePoints);
}

void Player::initializeSubComponents()
{
    for (auto &child : children)
    {
        child->initializeSubComponents();
    }
    battlefield->setPosition(getPosition() + battlefieldOffset);
    battlefield->reparent(this);
    addChild(battlefield);
    playerhand->setPosition(getPosition() + handOffset);
    playerhand->reparent(this);
    addChild(playerhand);
    playerHud->setPosition(getPosition());
    cardSelector->reparent(this);
    addChild(cardSelector);
    ui->addToHUDLayer(playerHud);
    ui->addToHUDLayer(cardSelector);
    playerBar->initializeSubComponents();
    playerBar->setPosition(getPosition() + lifePointOffset);
    playerBar->setRotation(-90);
    playerBar->setFillFactor((float)lifePoints / Settings::StartLifePoints);
    addChild(playerBar);
    playerManaBars->initializeSubComponents();
    playerManaBars->setPosition(getPosition() + manaBarOffset);
    playerManaBars->setRotation(-90);
    addChild(playerManaBars);
    playerCard->setMaxHealth(lifePoints);
    playerCard->setHealth(lifePoints);
    playerCard->setOwner(this);
    auto playerCardUI = playerCard->getCardUI();
    //playerCardUI->setPosition(getPosition());
    //playerCardUI->isVisible = false;
    //addChild(playerCard);
}

/*
The player represents a physical player at the table.
He has a hand, deck, graveyard, the ability to play cards and whatnot.
He cannot flip the table, though (yet?).
*/
Player::Player(UISystem *ui) : UIElement(ui),
                               playerhand{std::make_shared<Hand>(ui)},
                               battlefield{std::make_shared<Battlefield>(ui)},
                               playerBar{std::make_shared<Bar>(ui)},
                               cardSelector{std::make_shared<CardSelector>(ui)},
                               playerManaBars{std::make_shared<ManaBars>(ui, 50, 25)},
                               playerHud{std::make_shared<PlayerHUD>(ui)},
                               playerCard{std::make_shared<PlayerCard>()}
{
    name = "Player";
}

Player::Player(UISystem *ui, std::string Name) : Player(ui)
{
    this->name = Name;
}

/*
Tries to remove the card cardToRemove from the player's deck.
Throws an error if nothing was removed.
*/
shared_ptr<Card> Player::removeCardFromDeck(Card *cardToRemove)
{
    for (auto c : deck)
    {
        if (c.get() == cardToRemove)
        {
            deck.remove(c);
            //children.remove(c);
            cardToRemove->getCardUI()->reparent(nullptr);
            return c;
        }
    }
    cout << "Player: Tried to remove card that isn\'t in the deck\n";
    throw;
}

/*
Removes the topmost card from the deck, e.g. when the player draws a card.
Throws an error if deck is empty.
*/
shared_ptr<Card> Player::removeCardFromDeckTop()
{
    if (deck.size() < 1)
    {
        cout << "Player: No cards in deck to draw from.\n";
        throw;
    }
    auto c = *deck.rbegin();
    deck.remove(c);
    //children.remove(c);
    c->getCardUI()->reparent(nullptr);
    return c;
}

/*
When confronted with the choice on what cards to target, the player can choose by clicking highlighted cards.
Type/Amount/etc. of cards to select from can be ocnfigures via cardSelectionInfo.
*/
void Player::startSelection(CardSelectionInfo cardSelectionInfo)
{
    Player *enemy = game->getNextTurnPlayer();
    list<Card *> eligibleCards;
    if (cardSelectionInfo.enemyBattlefield || cardSelectionInfo.canAttackHeroDirectly)
    {
        bool heroAdded = false;
        if (cardSelectionInfo.enemyBattlefield){
            auto c = enemy->battlefield->getCards();
            eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
            if (c.size() == 0 && cardSelectionInfo.canAttackHero){
                eligibleCards.push_back(enemy->playerCard.get());
                heroAdded = true;
            }
        }
        if (cardSelectionInfo.canAttackHeroDirectly && !heroAdded){
            eligibleCards.push_back(enemy->playerCard.get());            
        }
    }
    if (cardSelectionInfo.selfBattlefield)
    {
        auto c = this->battlefield->getCards();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    if (cardSelectionInfo.enemyHand)
    {
        auto c = enemy->getHand();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    if (cardSelectionInfo.selfHand)
    {
        auto c = this->getHand();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    cardSelector->bIsCurrentlySelecting = true;
    cardSelector->setSelectionTarget(eligibleCards, false, cardSelectionInfo);
}

/*
When it's the players turn, he can select a card to tap it, move it, etc.
*/
void Player::selectCard(const Card *cardToSelect)
{
    selectedCard = cardToSelect;
    if (!cardSelector->bIsCurrentlySelecting)
    {
        playerHud->selectCard(cardToSelect);
    }
}

void Player::cardSelectionUpdated()
{
    if (awaitingSelection)
    {
        awaitingSelection->onReceiveSelection(cardSelector->getSelectedCards());
        cardSelector->resetSelection();
        awaitingSelection = nullptr;
    }
};
