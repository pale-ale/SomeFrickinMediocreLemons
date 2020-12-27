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
}

void Game::tick(){
}

