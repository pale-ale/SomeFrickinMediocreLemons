#include "Debugging.h"
#include "Game.h"
#include "Player.h"

using Debugging::log;

Player *Game::getNextTurnPlayer()
{
    if (players.size() < 1)
    {
        log("Game", "getNextTurnPlayer(): No players to get from.)");
        return nullptr;
    }
    int advanceCount = 0;
    auto player_it = players.begin();
    if (currentTurnPlayer)
    {
        while (player_it != players.end())
        {
            if (*player_it == currentTurnPlayer)
            {
                advanceCount++;
                break;
            }
            player_it++;
            advanceCount++;
        }
        advanceCount %= players.size();
    }
    else
    {
        advanceCount = rand() % players.size();
    }
    player_it = players.begin();
    advance(player_it, advanceCount);
    return *player_it;
}

void Game::addPlayer(Player *player)
{
    if (players.size() == 1)
    {
        player->setPosition({Settings::defaultWidth / 2, 0});
        player->setRotation(180);
    }
    else
    {
        player->setPosition({Settings::defaultWidth / 2, Settings::defaultHeight});
    }
    player->setGame(this);
    players.push_back(player);
    if (players.size() == 2)
    {
        for (auto p : players)
        {
            p->addMana({20, 20, 15, 7, 10});
        }
    }
}

void Game::startTurnOfPlayer(Player *player)
{
    if (currentTurnPlayer)
    {
        currentTurnPlayer->bIsMyTurn = false;
    }
    currentTurnPlayer = player;
    currentTurnPlayer->bIsMyTurn = true;
}

void Game::startTurnOfNextPlayer()
{
    startTurnOfPlayer(getNextTurnPlayer());
}
