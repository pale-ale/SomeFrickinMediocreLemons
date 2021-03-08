#include "SceneManager.h"
#include "iostream"

using std::cout;

void SceneManager::loadScene(SceneBase* newScene){
    if (currentScene){
        currentScene->cleanup();
    }
    cout << "loaidng new scene...\n";
    newScene->setup();
    currentScene = newScene;
}