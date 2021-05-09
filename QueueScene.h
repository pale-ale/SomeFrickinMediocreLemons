#pragma once

#include <SFML/Graphics.hpp>

#include "Debugging.h"
#include "Scene.h"

#include "net/Connector.h"

#include "ui/Button.h"
#include "ui/UISystem.h"

using Debugging::log;

class MainMenuScene;
class SceneManager;

class QueueScene: public SceneBase{
    public:
    QueueScene(UISystem* ui, SceneManager *sm, Connector *connector):SceneBase(ui,sm,connector){}
    sf::Font font;
    sf::Text queueLabel;
    sf::Text cancelQueueLabel;
  
    shared_ptr<Button> cancelQueueButton = make_shared<Button>(
        ui, 
        sf::Color{100,100,100,255}, 
        sf::Color{75,75,75,255}, 
        vector<sf::Vector2f>{
            {-55, -20},
            {-55, 20},
            {55, 20},
            {55, -20}
        });
    void setup() override;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
        SceneBase::draw(target, state);
        target.draw(*cancelQueueButton);
        target.draw(cancelQueueLabel);
        target.draw(queueLabel);
    };

    virtual void cleanup() override{
        log("MainMenuScene", "Running cleanup (currently does nothing)\n");
    }

    void loadPlaySceneButtonCallback();
    void playMultiPlayerButtonCallback();
};