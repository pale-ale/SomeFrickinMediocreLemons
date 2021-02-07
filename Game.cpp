#include "Game.h"

Game::Game(): 
sf::Drawable(){
    string filename = "/usr/share/test/resources/Tabletop.png";
    if (texture.loadFromFile(filename)){
        mainTexture.setTexture(texture);
        cout << "Loaded texture.\n";
    }
    else{
        cout << "Couldn't load texture at \'" << filename << "\'.\n";
        throw;
    }
    auto testFont = sf::Font();
    for (const char* testPath : Settings::defaultFontPaths){
        if(testFont.loadFromFile(testPath)){
            Settings::validFontPath = testPath;
            break;
        }
    }
    if (!Settings::validFontPath){
        cout << "No valid fontpath found.\n";
        throw;
    }
}

Player* Game::getNextTurnPlayer(){
    if (players.size() < 1){
        cout << "No players to start game\n";
        return nullptr;
    }
    int advanceCount = 0;
    auto player_it = players.begin();
    if (currentTurnPlayer){
        while (player_it != players.end()){
            if(*player_it == currentTurnPlayer){
                advanceCount++;
                break;
            }
            player_it++;
            advanceCount++;
        }
        advanceCount %= players.size();
    }else{
        advanceCount = rand() % players.size();
    }
    player_it = players.begin();
    advance(player_it, advanceCount);
    return *player_it;
}

void Game::addPlayer(Player* player){
    if (players.size() == 1){
        player->setPosition({Settings::defaultWidth/2, 0});
        player->setRotation(180);
    }else{
        player->setPosition({Settings::defaultWidth/2, Settings::defaultHeight});
    }
    player->setGame(this);
    players.push_back(player);
}

void Game::startTurnOfPlayer(Player* player){
    if (currentTurnPlayer){
        currentTurnPlayer->bIsMyTurn = false;
    }
    currentTurnPlayer = player;
    currentTurnPlayer->bIsMyTurn = true;
}

void Game::startTurnOfNextPlayer(){
    startTurnOfPlayer(getNextTurnPlayer());
}