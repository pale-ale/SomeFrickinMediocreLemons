#include "Battlefield.h"

Battlefield::Battlefield(UISystem *ui)
{
    name = "Battlefield";
}

void Battlefield::addCard(shared_ptr<card> newCard, bool support, int slot)
{
    auto row = support ? &supportCards : &battleCards;
    int max = support ? MAX_SUPPORT_CARDS : MAX_BATTLE_CARDS;
    if (slot == -1)
    {
        slot = getNextFreeSlot(*row, max);
    }
    if (slot == -1)
    {
        cout << "No free slots to add to!" << endl;
        throw;
    }
    if (slot >= MAX_SUPPORT_CARDS)
    {
        cout << "Invalid slot index." << endl;
        throw;
    }
    row->push_back({slot, newCard});
    newCard->reparent(this);
    addChild(newCard);
    newCard->cardLocation = ECardLocation::battlefield;
    newCard->setPosition(transform.getTransform().transformPoint(
        (support ? supportPositionsOffset[slot] : battlePositionsOffset[slot])));
    newCard->setRotation(0);
}

void Battlefield::removeCard(int slot, bool support)
{
    auto row = support ? supportCards : battleCards;
    auto card = getCardAt(slot, support);
    if (card)
    {
        removeChild(card);
        card->reparent(nullptr);
        row.remove_if([slot](cardIndex ci){return ci.index == slot;});
    }
    else
    {
        cout << "Trying to remove card in empty slot!\n";
        throw;
    }
}

void Battlefield::removeCard(card *cardToRemove)
{
    cout << "trying to remove card " << cardToRemove->getName() << endl;
    for (auto cardIndex : battleCards){
        auto c = cardIndex._card.get();
        if (c == cardToRemove)
        {
            cout << "Removing battle card\n";
            battleCards.remove(cardIndex);
            removeChild(c);
            c->reparent(nullptr);
            return;
        }
    }
    
    for (auto cardIndex : supportCards){
        auto c = cardIndex._card.get(); 
        if (c == cardToRemove){
            cout << "Removing support card\n";
            supportCards.remove(cardIndex);
            removeChild(c);
            c->reparent(nullptr);
            return;
        }
    }
    cout << "card is not on the battlefield.\n";
    throw;
}

card* Battlefield::getCardAt(int slot, bool support)
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

void Battlefield::printCards(){
    cout << "Battle cards:\n";
    for (auto cardindex : battleCards){
        cout << "Card: " << cardindex._card->getName() << ", index: " << cardindex.index << endl;
    }
    cout << "Support cards:\n";
    for (auto cardindex : supportCards){
        cout << "Card: " << cardindex._card->getName() << ", index: " << cardindex.index << endl;
    }
}

int Battlefield::getNextFreeSlot(list<cardIndex> &cards, int max)
{
    for (int check = 0; check < max; check++)
    {
        bool freeSlotFound = true;
        for (cardIndex &ci : cards)
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

list<card*> Battlefield::getCards() const
{
    list<cardIndex> cis;
    cis.insert(cis.end(), supportCards.begin(), supportCards.end());
    cis.insert(cis.end(), battleCards.begin(), battleCards.end());
    list<card*> cards;
    for (auto ci : cis)
    {
        cards.push_back(ci._card.get());
    }
    return cards;
}