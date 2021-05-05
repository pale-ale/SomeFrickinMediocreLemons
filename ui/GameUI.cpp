#include "GameUI.h"
#include "../Player.h"

GameUI::GameUI(Game *game) : sf::Drawable(), game{game}
{
    if (texture.loadFromFile(string(Settings::programDir) + Settings::relativeAssetTabletopPath))
    {
        mainTexture.setTexture(texture);
        cout << "Game: Loaded tabletop texture.\n";
    }
    else
    {
        cout << "Game: Couldn't find tabletop texture at \'" << Settings::programDir << Settings::relativeAssetTabletopPath << "\'. Exiting.\n";
        throw;
    }
}

void GameUI::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mainTexture, states);
    auto playerIterator = game->players.begin();

    while (playerIterator != game->players.end())
    {
        target.draw(**playerIterator);
        playerIterator++;
    }
}