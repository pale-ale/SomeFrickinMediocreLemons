#pragma once

#include "Scene.h"
#include <memory>
#include "Debugging.h"
#include "GameScene.h"
#include "QueueScene.h"
#include "MainMenuScene.h"

using Debugging::log;

class Connector;
class UISystem;

class SceneManager{
    public:
    SceneManager(UISystem *ui, Connector *connector): connector{connector}, ui{ui}{}
    template<class TSubclassOfScene>
    void loadScene(){
        if (currentScene){
            log("SceneManager", "Starting cleanup of old scene....\n");
            currentScene->cleanup();
            cout << "SceneManager: Old scene finished cleanup.\n";
        }
        log("SceneManager", "Loading new scene...\n");
        auto newScene = std::make_shared<TSubclassOfScene>(ui, this, connector);
        newScene->setup();
        currentScene = std::move(newScene);
        log("SceneManager", "Done loading scene.\n");
    }
    SceneBase* getScene(){return currentScene.get();}
    private:
    std::shared_ptr<SceneBase> currentScene = nullptr;
    Connector *connector = nullptr;
    UISystem *ui = nullptr;
};