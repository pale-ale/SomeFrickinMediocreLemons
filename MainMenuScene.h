#include <SFML/Graphics.hpp>

#include "Scene.h"

#include "net/Connector.h"
#include "ui/Button.h"
#include "ui/UISystem.h"

class MainMenuScene: public SceneBase{
    UISystem* ui;
    Connector *connector;
    public:
    MainMenuScene(UISystem* ui, SceneManager &sm, Connector *connector):SceneBase(&sm), ui{ui}, connector{connector}{}
    sf::Font font;
    sf::Text mainMenuLabel;
    sf::Text playOnlineLabel;
    sf::Text playOfflineLabel;
    sf::Text settingsLabel;
    shared_ptr<Button> playOnlineButton = make_shared<Button>(
        ui, 
        sf::Color{100,100,100,255}, 
        sf::Color{75,75,75,255}, 
        vector<sf::Vector2f>{
            {-50, -20},
            {-50, 20},
            {50, 20},
            {50, -20}
        });
    shared_ptr<Button> playOfflineButton = make_shared<Button>(
        ui, 
        sf::Color{100,100,100,255}, 
        sf::Color{75,75,75,255}, 
        vector<sf::Vector2f>{
            {-50, -20},
            {-50, 20},
            {50, 20},
            {50, -20}
        });
    void setup() override;
    void setGameScene(unique_ptr<SceneBase> scene){gameScene.swap(scene);}

    private:
    sf::Vector2f playOnlinePos;
    sf::Vector2f playOfflinePos;
    sf::Vector2f settingsPos;
    unique_ptr<SceneBase> gameScene = nullptr;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
        SceneBase::draw(target, state);
        target.draw(*playOnlineButton);
        target.draw(playOnlineLabel);
        target.draw(*playOfflineButton);
        target.draw(playOfflineLabel);
        target.draw(settingsLabel);
        target.draw(mainMenuLabel);
    };

    virtual void cleanup() override{
        cout << "MainMenuScene: Running cleanup (currently does nothing)\n";
    }

    void loadPlaySceneButtonCallback(){
        connector->hostGame();
        if (gameScene){
            sceneManager->loadScene(std::move(gameScene));
        }
    }

    void playMultiPlayerButtonCallback(){
        connector->connectToGame();
    }
};