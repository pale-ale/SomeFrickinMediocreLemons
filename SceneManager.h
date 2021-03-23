#pragma once

#include "Scene.h"

class SceneBase;

class SceneManager{
    private:
    std::unique_ptr<SceneBase> currentScene = nullptr;
    public:
    void loadScene(std::unique_ptr<SceneBase> newScene);
    SceneBase* getScene(){return currentScene.get();}
};