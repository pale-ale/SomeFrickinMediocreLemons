#include "events/EventCallback.h"
#include <iostream>
#include "MainMenuScene.h"
#include "Settings.h"

using std::cout;

void MainMenuScene::setup(){
    cout << "MainMenuScene: Setting up mainmenu...\n";
    playOnlineButton->initializeSubComponents();
    playOnlineButton->setName("OnlineButton");
    playOfflineButton->initializeSubComponents();
    playOfflineButton->setName("OfflineButton");
    playOnlinePos = {Settings::defaultWidth/2 - 60, Settings::defaultWidth/2 - 100};
    playOfflinePos = {Settings::defaultWidth/2 + 60, Settings::defaultWidth/2 - 100};
    settingsPos = {Settings::defaultWidth/2, Settings::defaultWidth/2};
    sf::FloatRect s;
    font.loadFromFile(Settings::validFontPath);
    mainMenuLabel.setFont(font);
    mainMenuLabel.setString("Main Menu");
    s = mainMenuLabel.getLocalBounds();
    mainMenuLabel.setPosition({Settings::defaultWidth/2 - s.width/2, Settings::defaultHeight/2-s.height/2-100});
    playOnlineLabel.setFont(font);
    playOnlineLabel.setString("MP");
    playOfflineLabel.setFont(font);
    playOfflineLabel.setString("SP");
    s = playOnlineLabel.getLocalBounds();
    playOnlineLabel.setPosition(playOnlinePos + sf::Vector2f{-s.width/2, -s.height/2});
    s = playOfflineLabel.getLocalBounds();
    playOfflineLabel.setPosition(playOfflinePos + sf::Vector2f{-s.width/2, -s.height/2});
    settingsLabel.setFont(font);
    settingsLabel.setString("Settings");
    s = settingsLabel.getLocalBounds();
    settingsLabel.setPosition(settingsPos + sf::Vector2f{-s.width/2, -s.height/2});
    
    playOnlineButton->setDefaultColor({100,100,120,255});
    playOnlineButton->setMouseoverColor({80,80,100,255});
    s = playOnlineLabel.getLocalBounds(); 
    playOnlineButton->setPosition(playOnlinePos + sf::Vector2f{2.5,5});
    playOnlineButton->onMouseDownCallback = std::make_shared<EventCallback<MainMenuScene>>(this, &MainMenuScene::loadPlaySceneButtonCallback);
   
    playOfflineButton->setDefaultColor({100,100,120,255});
    playOfflineButton->setMouseoverColor({80,80,100,255});
    s = playOfflineLabel.getLocalBounds(); 
    playOfflineButton->setPosition(playOfflinePos + sf::Vector2f{2.5,5});
    playOfflineButton->onMouseDownCallback = std::make_shared<EventCallback<MainMenuScene>>(this, &MainMenuScene::playMultiPlayerButtonCallback);
}