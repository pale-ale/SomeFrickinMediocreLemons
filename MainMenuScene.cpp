#include "MainMenuScene.h"
#include "iostream"
#include "Settings.h"
#include "Events/EventCallback.h"

using std::cout;

void MainMenuScene::setup(){
    playPos = {Settings::defaultWidth/2, Settings::defaultWidth/2 - 100};
    settingsPos = {Settings::defaultWidth/2, Settings::defaultWidth/2};
    sf::FloatRect s;
    font.loadFromFile(Settings::validFontPath);
    mainMenuLabel.setFont(font);
    mainMenuLabel.setString("Main Menu");
    s = mainMenuLabel.getLocalBounds();
    mainMenuLabel.setPosition({Settings::defaultWidth/2 - s.width/2, Settings::defaultHeight/2-s.height/2-100});
    playLabel.setFont(font);
    playLabel.setString("Play");
    s = playLabel.getLocalBounds();
    playLabel.setPosition(playPos + sf::Vector2f{-s.width/2, -s.height/2});
    settingsLabel.setFont(font);
    settingsLabel.setString("Settings");
    s = settingsLabel.getLocalBounds();
    settingsLabel.setPosition(settingsPos + sf::Vector2f{-s.width/2, -s.height/2});
    playButton.setColor({100,100,120,255});
    s = playLabel.getLocalBounds(); 
    playButton.setSize({s.width*1.1f, s.height*1.1f});
    playButton.setPosition(playPos + sf::Vector2f{2.5,5});
    playButton.onMouseDownCallback = new EventCallback<MainMenuScene>(this, &MainMenuScene::loadPlaySceneButtonCallback);
}