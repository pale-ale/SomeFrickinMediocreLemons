#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

/*
Scenes are going to be the containers of... well... the scene?
Every non-elementary object (meaning cards, UIElements, players, battlefields etc. but not the uisystem)
will live inside a scene.
Each scene will have to inherit from BaseScene, which will provide a setup, tick, and cleanup function 
in addition to the normal *'tors.
The main.cpp will then only contain things like: scene x = CoolScene(UISystem, ...), x.tick() and so forth. 
Everything game related is to be put into an according scene.
This way it'll be easy to build different environments, like the battlefield and the main menu, the deck builder etc.
It also facilitates the "switching" of such environments, since we dont have to remove every single ui/non-ui object
but can rather make them be owned by our scene and destroy it or make it invisible.
This'll bring the added benefit of preloading some scenes or assets or easy loading screens.
*/
class SceneManager;
class SceneBase : public sf::Drawable{
    protected:

    SceneManager* sceneManager;
    public:
    SceneBase(SceneManager *sceneManager):sceneManager{sceneManager}{}
    SceneBase() = delete;
    ~SceneBase(){std::cout << "SceneBase: Destroying scene.\n";}
    virtual void setup(){}
    virtual void tick(float deltaTime){}
    virtual void cleanup(){}

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {};
};