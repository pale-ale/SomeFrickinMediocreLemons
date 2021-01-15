#include "Battlefield.h"

Battlefield::Battlefield(){
    supportCards = vector<cardIndex>();
    battleCards = vector<cardIndex>();
}

void Battlefield::AddCard(card& newCard, bool support, int slot){
    auto row = support ? &supportCards : &battleCards;
    int max = support ? MAX_SUPPORT_CARDS : MAX_BATTLE_CARDS;
    if (slot == -1){
        slot = getNextFreeSlot(*row, max);
    }
    if (slot == -1){
        cout << "No free slots to add to!" << endl; throw;
    }
    if (slot >= MAX_SUPPORT_CARDS){
        cout << "Invalid slot index." << endl; throw;
    }
    row->push_back({slot, &newCard});
    newCard.SetPosition(support ? supportPositions[slot] : battlePositions[slot]);
}

void Battlefield::RemoveCard(int slot, bool support){
    auto row = support ? supportCards : battleCards;
    int rowIndex;
    auto card = getCardAt(slot, rowIndex, support);
    if (card){
        row.erase(row.begin() + rowIndex);
    }else{
        cout << "Trying to remove card in empty slot!\n"; throw;
    }
}

card* Battlefield::getCardAt(int slot, int& inIndex, bool support){
    auto row = support ? supportCards : battleCards;
    for (int i=0; i<row.size(); i++){
        if (row[i].index == slot){ 
            inIndex = i;
            return row[i]._card;
        }
    }
    return nullptr;
}

int Battlefield::getNextFreeSlot(vector<cardIndex>& cards, int max){
    for (int check=0; check<max; check++){
        for (cardIndex ci : cards){
            if (ci.index == check){ continue; }
        }
        return check;
    }
    return -1;
}
