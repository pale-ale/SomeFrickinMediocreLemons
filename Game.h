#pragma once

#include <list>
#include <random>

class Player;

class Game{
    public:
    std::list<Player*> players = {};
    void addPlayer(Player* player);

    Player* currentTurnPlayer = nullptr;
    Player* getNextTurnPlayer();
    void startTurnOfPlayer(Player* player);
    void startTurnOfNextPlayer();
};
