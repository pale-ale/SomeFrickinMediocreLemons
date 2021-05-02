#include "Battlefield.h"
#include "ui/CardUI.h"

Battlefield::Battlefield(UISystem *ui){
    this->ui = ui;
    name = "Battlefield";
}

ECardLocation Battlefield::positionToCardLocation(int index, bool support){
    if (support){
        return index == 0 || index == 3 ? ECardLocation::battlefieldSupport : ECardLocation::battlefieldBattort;
    }
    return ECardLocation::battlefieldBattle;
}

void Battlefield::addCard(shared_ptr<Card> newCard, bool support, int slot)
{
    auto row = support ? &supportCards : &battleCards;
    int max = support ? MAX_SUPPORT_CARDS : MAX_BATTLE_CARDS;
    if (slot == -1){
        slot = getNextFreeSlot(support);
    }
    if (slot == -1)
    {
        cout << "Battlefield: No free slots to add to!" << endl;
        throw;
    }
    if (slot >= MAX_SUPPORT_CARDS)
    {
        cout << "Battlefield: Invalid slot index: \'" << slot << "\'\n";
        throw;
    }
    auto newCardUI = newCard->getCardUI();
    row->push_back({slot, newCard});
    newCardUI->reparent(this);
    addChild(newCardUI);
    newCard->cardLocation = positionToCardLocation(slot, support);
    newCardUI->setPosition(toGlobal(support ? supportPositionsOffset[slot].pos : battlePositionsOffset[slot].pos));
    newCardUI->setRotation(0);
}

void Battlefield::removeCard(int slot, bool support)
{
    auto row = support ? supportCards : battleCards;
    auto card = getCardAt(slot, support);
    if (card)
    {
        auto cardUI = card->getCardUI();
        removeChild(cardUI.get());
        cardUI->reparent(nullptr);
        row.remove_if([slot](cardIndex ci){return ci.index == slot;});
    }
    else
    {
        cout << "Battlefield: Trying to remove card in empty slot!\n";
        throw;
    }
}

void Battlefield::removeCard(Card *cardToRemove)
{
    cout << "Battlefield: Trying to remove card " << cardToRemove->label << endl;
    for (auto cardIndex : battleCards){
        auto cicard = cardIndex._card;
        auto c = cicard.get();
        auto cUI = c->getCardUI();
        if (c == cardToRemove)
        {
            cout << "Battlefield: Removing battle card\n";
            battleCards.remove(cardIndex);
            removeChild(cUI.get());
            cUI->reparent(nullptr);
            return;
        }
    }
    
    for (auto cardIndex : supportCards){
        auto cicard = cardIndex._card;
        auto c = cicard.get(); 
        auto cUI = c->getCardUI();
        if (c == cardToRemove){
            cout << "Battlefield: Removing support card\n";
            supportCards.remove(cardIndex);
            removeChild(cUI.get());
            cUI->reparent(nullptr);
            return;
        }
    }
    cout << "Battlefield: Card is not on the battlefield.\n";
    throw;
}

Card* Battlefield::getCardAt(int slot, bool support)
{
    auto row = support ? supportCards : battleCards;
    for (auto &cardIndex : row)
    {
        if (cardIndex.index == slot)
        {
            return cardIndex._card.get();
        }
    }
    return nullptr;
}

void Battlefield::setDrawFreeSpaces(bool drawFreeSpaces, bool support){
    auto freeIndices = getFreeIndices(support);
    auto row = support ? supportPositionsOffset : battlePositionsOffset;
    if (drawFreeSpaces){
        for (int freeIndex : freeIndices){
            auto freeCardSpace = std::make_shared<sf::RectangleShape>(Settings::cardSize);
            freeCardSpace->setOrigin(Settings::cardSize * .5f);
            freeCardSpace->setScale(Settings::cardScale);
            freeCardSpace->setFillColor(sf::Color{255,255,100,100});
            freeCardSpace->setPosition(toGlobal(row[freeIndex].pos));
            emptySpaceDisplay.push_back(freeCardSpace);
        }
    }
    else{
        emptySpaceDisplay.clear();
    }
}

vector<sf::Vector2f> Battlefield::getFreeSnapPoints(bool support){
    vector<sf::Vector2f> snapPoints;
    auto freeIndices = getFreeIndices(support);
    auto row = support ? supportPositionsOffset : battlePositionsOffset;
    for (int freeIndex : freeIndices){
        snapPoints.push_back(toGlobal(row[freeIndex].pos));
    }
    return snapPoints;
}

void Battlefield::printCards(){
    cout << "Battlefield: Battle cards:\n";
    for (auto cardindex : battleCards){
        cout << "Card: " << cardindex._card->label << ", index: " << cardindex.index << endl;
    }
    cout << "Battlefield: Support cards:\n";
    for (auto cardindex : supportCards){
        cout << "Card: " << cardindex._card->label << ", index: " << cardindex.index << endl;
    }
}

int Battlefield::getNextFreeSlot(bool support)
{
    auto row = support ? supportCards : battleCards;
    int max = support ? MAX_SUPPORT_CARDS : MAX_BATTLE_CARDS;
    for (int check = 0; check < max; check++)
    {
        bool freeSlotFound = true;
        for (cardIndex &ci : row)
        {
            if (freeSlotFound && ci.index == check)
            {
                freeSlotFound = false;
            }
        }
        if (freeSlotFound)
        {
            return check;
        }
    }
    return -1;
}

list<Card*> Battlefield::getCards() const
{
    list<cardIndex> cis;
    cis.insert(cis.end(), supportCards.begin(), supportCards.end());
    cis.insert(cis.end(), battleCards.begin(), battleCards.end());
    list<Card*> cards;
    for (auto ci : cis)
    {
        cards.push_back(ci._card.get());
    }
    return cards;
}
