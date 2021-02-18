#include "Battlefield.h"

Battlefield::Battlefield(UISystem* ui)
{
    supportCards = vector<cardIndex>();
    battleCards = vector<cardIndex>();
}

void Battlefield::addCard(shared_ptr<card>& newCard, bool support, int slot)
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
    newCard->attachTo(this);
    newCard->cardLocation = ECardLocation::battlefield;
    newCard->setPosition(transform.getTransform().transformPoint(
                       (support ? supportPositionsOffset[slot] : battlePositionsOffset[slot])
                       ));
    newCard->setRotation(0);
}

void Battlefield::removeCard(int slot, bool support)
{
    auto row = support ? supportCards : battleCards;
    int rowIndex;
    auto card = getCardAt(slot, rowIndex, support);
    if (card)
    {
        removeChild(card.get());
        row.erase(row.begin() + rowIndex);
    }
    else
    {
        cout << "Trying to remove card in empty slot!\n";
        throw;
    }
}

void Battlefield::removeCard(shared_ptr<const card> cardToRemove){
    auto start = battleCards.begin();
    auto end = battleCards.end();
    while (start != end){
        auto card = (*start)._card;
        if (card == cardToRemove){
            cout << "Removing battle card\n";
            battleCards.erase(start);
            removeChild(card.get());
            return;
        }
        start++;
    }
    start = supportCards.begin();
    end = supportCards.end();
    while (start != end){
        auto card = (*start)._card;
        if (card == cardToRemove){
            cout << "Removing support card\n";
            supportCards.erase(start);
            removeChild(card.get());
            cout << card.use_count() << endl;
            return;
        }
        start++;
    }
}


shared_ptr<card> Battlefield::getCardAt(int slot, int &inIndex, bool support)
{
    auto row = support ? supportCards : battleCards;
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i].index == slot)
        {
            inIndex = i;
            return row[i]._card;
        }
    }
    return nullptr;
}

int Battlefield::getNextFreeSlot(vector<cardIndex> &cards, int max)
{
    for (int check = 0; check < max; check++)
    {
        bool freeSlotFound = true;
        for (cardIndex ci : cards)
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

list<shared_ptr<const card>> Battlefield::getCards() const{
    list<cardIndex> cis;
    cis.insert(cis.end(), supportCards.begin(), supportCards.end());
    cis.insert(cis.end(), battleCards.begin(), battleCards.end());
    list<shared_ptr<const card>> cards;
    for (auto ci : cis){
        cards.push_back(ci._card);
    }
    return cards;
}