#include <iostream>
#include <list>
#include "Player.h"
#include <random>
#include <SFML/Graphics.hpp>

class Game : public sf::Drawable{
    public:
    Game();
    list<Player*> players = {};
    void addPlayer(Player* player);
    sf::Sprite mainTexture = {};
    sf::Texture texture = {};

    Player* currentTurnPlayer = nullptr;
    Player* getNextTurnPlayer();
    void startTurnOfPlayer(Player* player);
    void startTurnOfNextPlayer();

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(mainTexture, states);
        auto playerIterator = players.begin();

        while (playerIterator != players.end()){
            target.draw(**playerIterator);
            playerIterator++;
        }
    }
};
