#include "card.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"

void Player::drawCards(int count)
{
    if (deck.size() < count)
    {
        cout << "Not enough cards to draw!\n";
        throw;
    }

    auto it = deck.rbegin();

    for (int i = 0; i < count; i++)
    {
        auto &card = *it;
        deck.pop_back();
        playerhand->addCardToHand(card);
        card->cardLocation = ECardLocation::hand;
        card->setFlipState(true);
    }

    playerhand->updateHandPositions();
    playerHud->setDeckCount(deck.size());
    playerHud->setHandCount(playerhand->getHand().size());
}

void Player::playCard(card *cardToPlay)
{
    auto sharedCardPtr = playerhand->removeCard(cardToPlay);
    mana -= cardToPlay->cost;
    playerManaBars->updateManaBars(&mana);
    battlefield->addCard(sharedCardPtr);
    cout << "Ref count after playing card (should be 3): " << sharedCardPtr.use_count() << endl;
    cout << "Player "
            << " played card " << cardToPlay->getName() << endl;
    playerhand->updateHandPositions();
    playerHud->setHandCount(playerhand->getHand().size());
    if (game)
    {
        game->startTurnOfNextPlayer();
    }
    else
    {
        cout << "I need a gameInstance!\n";
    }
}

void Player::addCardToDeck(shared_ptr<card> card)
{
    card->setPosition(transform.getTransform().transformPoint(deckOffset));
    card->setRotation(this->getRotation());
    card->setFlipState(false);
    card->owner = this;
    card->cardLocation = ECardLocation::deck;
    deck.push_back(card);
    playerHud->setDeckCount(deck.size());
    addChild(card);
}

void Player::addCardToGraveyard(shared_ptr<card> card)
{
    card->setPosition(this->getPosition() + graveyardOffset);
    card->setFlipState(false);
    card->owner = this;
    graveyard.push_back(card);
    addChild(card);
}

const list<card*> Player::getHand() const
{
    return playerhand->getHand();
}

void Player::printDeck() const
{
    cout << "Cards in deck:" << endl;
    for (auto &c : deck)
    {
        cout << "\t" + c->getName() << endl;
    }
}

void Player::printHand() const
{
    auto hand = playerhand->getHand();
    auto start = hand.begin();
    auto end = hand.end();
    cout << "Cards in hand: " << hand.size() << endl;
    while (start != end)
    {
        cout << "\t" + (*start)->getName() << endl;
        start++;
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

Player::Player(UISystem *ui, std::string Name) : Player(ui)
{
    this->mana = FMana();
    this->name = Name;
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

void Player::initializeSubComponents(){
    battlefield->setPosition(getPosition() + battlefieldOffset);
    battlefield->reparent(shared_from_this());
    addChild(battlefield);
    playerhand->setPosition(getPosition() + handOffset);
    playerhand->reparent(shared_from_this());
    addChild(playerhand);
    playerHud->setPosition(getPosition());
    addChild(cardSelector);
    ui->addToHUD(playerHud.get());
    ui->addToHUD(cardSelector.get());
    playerBar->setPosition(getPosition() + lifePointOffset);
    playerBar->setRotation(-90);
    addChild(playerBar);
    playerBar->setFillFactor((float)lifePoints / Settings::StartLifePoints);
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

void Player::startSelection(CardSelectionInfo cardSelectionInfo)
{
    Player *enemy = game->getNextTurnPlayer();
    list<card*> eligibleCards;
    if (cardSelectionInfo.enemyBattlefield){
        auto c = enemy->battlefield->getCards();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    if (cardSelectionInfo.selfBattlefield){
        auto c = this->battlefield->getCards();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    if (cardSelectionInfo.enemyHand){
        auto c = enemy->getHand();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    if (cardSelectionInfo.selfHand){
        auto c = this->getHand();
        eligibleCards.insert(eligibleCards.end(), c.begin(), c.end());
    }
    cardSelector->bIsCurrentlySelecting = true;
    cardSelector->setSelectionTarget(eligibleCards, false, cardSelectionInfo);
}

void Player::previewCard(std::shared_ptr<const card> cardToPreview)
{
    if (!cardSelector->bIsCurrentlySelecting)
    {
        playerHud->generatePreview(cardToPreview);
    }
}

void Player::stopPreviewingCard()
{
    playerHud->removePreview();
}
