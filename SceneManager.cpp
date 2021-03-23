#include "SceneManager.h"
#include "iostream"

using std::cout;

void SceneManager::loadScene(std::unique_ptr<SceneBase> newScene){
    if (currentScene){
        cout << "SceneManager: Starting cleanup of old scene....\n";
        currentScene->cleanup();
        cout << "SceneManager: Old scene finished cleanup.\n";
    }
    cout << "SceneManager: Loading new scene...\n";
    newScene->setup();
    currentScene = std::move(newScene);
    cout << "SceneManager: Done loading scene.\n";
}