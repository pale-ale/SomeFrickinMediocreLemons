#pragma once

#include <iostream>
#include <list>
#include <random>
#include <SFML/Graphics.hpp>

#include "../Game.h"

class Player;

class GameUI : public sf::Drawable{
    public:
    GameUI(Game *game);
    sf::Sprite mainTexture = {};
    sf::Texture texture = {};

    private:
    Game *game = nullptr;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
