#include "Card.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"

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
    playerHud->setHandCount(playerhand->getHand().size());
}

void Player::playCard(Card *cardToPlay, int slot)
{
    auto sharedCardPtr = playerhand->removeCard(cardToPlay);
    mana -= cardToPlay->cost;
    playerManaBars->updateManaBars(&mana);
    battlefield->addCard(sharedCardPtr, true, slot);
    cout << "Player: " << name << " played card " << cardToPlay->getName() << endl;
    playerhand->updateHandPositions();
    playerHud->setHandCount(playerhand->getHand().size());
    if (game)
    {
        game->startTurnOfNextPlayer();
    }
    else
    {
        cout << "Player: I need a gameInstance!\n";
    }
}

void Player::addCardToDeck(shared_ptr<Card> card)
{
    card->setPosition(transform.getTransform().transformPoint(deckOffset));
    card->setRotation(this->getRotation());
    card->setFlipState(false);
    card->setOwner(this);
    card->cardLocation = ECardLocation::deck;
    deck.push_back(card);
    playerHud->setDeckCount(deck.size());
    addChild(card);
}

void Player::addCardToGraveyard(shared_ptr<Card> card)
{
    card->setPosition(this->getPosition() + graveyardOffset);
    card->setFlipState(false);
    card->setOwner(this);
    graveyard.push_back(card);
    addChild(card);
}

const list<Card *> Player::getHand() const
{
    return playerhand->getHand();
}

void Player::printDeck() const
{
    cout << "Player: Cards in deck:" << deck.size() << endl;
    for (auto &c : deck)
    {
        cout << "\t" + c->getName() << endl;
    }
}

void Player::printHand() const
{
    auto hand = playerhand->getHand();
    cout << "Player: Cards in hand: " << hand.size() << endl;
    for (auto &c : hand)
    {
        cout << "\t" + c->getName() << endl;
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
    ui->addToHUD(playerHud.get());
    ui->addToHUD(cardSelector.get());
    playerBar->initializeSubComponents();
    playerBar->setPosition(getPosition() + lifePointOffset);
    playerBar->setRotation(-90);
    playerBar->setFillFactor((float)lifePoints / Settings::StartLifePoints);
    addChild(playerBar);
    playerManaBars->initializeSubComponents();
    playerManaBars->setPosition(getPosition() + manaBarOffset);
    playerManaBars->setRotation(-90);
    addChild(playerManaBars);
}

Player::Player(UISystem *ui) : UIElement(ui),
                               playerhand{std::make_shared<Hand>(ui)},
                               battlefield{std::make_shared<Battlefield>(ui)},
                               playerBar{std::make_shared<Bar>(ui)},
                               cardSelector{std::make_shared<CardSelector>(ui)},
                               playerManaBars{std::make_shared<ManaBars>(ui, 50, 25)},
                               playerHud{std::make_shared<PlayerHUD>(ui)}
{
    name = "Player";
}

Player::Player(UISystem *ui, std::string Name) : Player(ui)
{
    this->name = Name;
}

shared_ptr<Card> Player::removeCardFromDeck(Card *cardToRemove)
{
    for (auto c : deck)
    {
        if (c.get() == cardToRemove)
        {
            deck.remove(c);
            children.remove(c);
            cardToRemove->reparent(nullptr);
            return c;
        }
    }
    cout << "Player: Tried to remove card that isn\'t in the deck\n";
    throw;
}

shared_ptr<Card> Player::removeCardFromDeckTop()
{
    if (deck.size() < 1)
    {
        cout << "Player: No cards in deck to draw from.\n";
        throw;
    }
    auto c = *deck.rbegin();
    deck.remove(c);
    children.remove(c);
    c->reparent(nullptr);
    return c;
}

void Player::startSelection(CardSelectionInfo cardSelectionInfo)
{
    Player *enemy = game->getNextTurnPlayer();
    list<Card *> eligibleCards;
    if (cardSelectionInfo.enemyBattlefield)
    {
        auto c = enemy->battlefield->getCards();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
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

void Player::previewCard(const Card *cardToPreview)
{
    if (!cardSelector->bIsCurrentlySelecting)
    {
        playerHud->previewCard(cardToPreview);
    }

}

void Player::selectCard(const Card *cardToSelect)
{
    if (!cardSelector->bIsCurrentlySelecting)
    {
        playerHud->selectCard(cardToSelect);
    }
}

void Player::stopPreviewingCard()
{
    playerHud->previewCard(nullptr);
}
