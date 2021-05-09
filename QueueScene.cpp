#include <iostream>
#include "events/EventCallback.h"
#include "QueueScene.h"
#include "Settings.h"
#include "SceneManager.h"

using std::cout;

void QueueScene::setup(){
    log("QueueScene", "Loading...\n");
    cancelQueueButton->initializeSubComponents();
    cancelQueueButton->setName("CancelQueueButton");
    font.loadFromFile(Settings::validFontPath);
    queueLabel.setFont(font);
    queueLabel.setString("Searching game...");
    auto s = queueLabel.getLocalBounds();
    queueLabel.setPosition({Settings::defaultWidth/2 - s.width/2, Settings::defaultHeight/2-s.height/2-100});

    cancelQueueLabel.setFont(font);
    cancelQueueLabel.setString("Cancel");
    s = cancelQueueLabel.getLocalBounds();
    cancelQueueLabel.setPosition({Settings::defaultWidth/2 - s.width/2, Settings::defaultWidth/2-s.height/2-5});
   
    cancelQueueButton->setDefaultColor({100,100,120,255});
    cancelQueueButton->setMouseoverColor({80,80,100,255});
    cancelQueueButton->setPosition({Settings::defaultWidth/2, Settings::defaultWidth/2});
    cancelQueueButton->onMouseDownCallback = std::make_shared<EventCallback<QueueScene>>(this, &QueueScene::loadPlaySceneButtonCallback);
}

void QueueScene::loadPlaySceneButtonCallback(){
    sceneManager->loadScene<MainMenuScene>();
}

void QueueScene::playMultiPlayerButtonCallback(){
    connector->connectToGame();
    connector->sendJoinRequest();
}