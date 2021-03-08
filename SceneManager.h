#pragma once

#include "Scene.h"

class SceneBase;

class SceneManager{
    private:
    SceneBase* currentScene = nullptr;
    public:
    void loadScene(SceneBase* newScene);
    SceneBase* getScene(){return currentScene;}
};