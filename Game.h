#pragma once

#include <iostream>
#include <list>
#include <random>
#include <SFML/Graphics.hpp>

class Player;

class Game : public sf::Drawable{
    public:
    Game();
    std::list<Player*> players = {};
    void addPlayer(Player* player);
    sf::Sprite mainTexture = {};
    sf::Texture texture = {};

    Player* currentTurnPlayer = nullptr;
    Player* getNextTurnPlayer();
    void startTurnOfPlayer(Player* player);
    void startTurnOfNextPlayer();

    private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
