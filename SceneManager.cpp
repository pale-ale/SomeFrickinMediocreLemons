#include "SceneManager.h"
#include "iostream"

using std::cout;

void SceneManager::loadScene(SceneBase* newScene){
    if (currentScene){
        currentScene->cleanup();
        delete currentScene;
        cout << "old scene finished cleanup.\n";
    }
    cout << "loading new scene...\n";
    newScene->setup();
    currentScene = newScene;
    cout << "done loading scene.\n";
}