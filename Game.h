#include <list>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

class Game : public sf::Drawable{
    public:
    Game();
    list<Player*> players = {};
    void addPlayer(Player* player);
    sf::Sprite mainTexture = {};
    sf::Texture texture = {};

    Player* currentTurnPlayer;
    Player* getNextTurnPlayer();

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
