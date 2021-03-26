#include "Scene.h"
#include <SFML/Graphics.hpp>
#include "ui/UISystem.h"
#include "ui/Button.h"

class MainMenuScene: public SceneBase{
    UISystem* ui;
    public:
    sf::Font font;
    sf::Text mainMenuLabel;
    sf::Text playLabel;
    sf::Text settingsLabel;
    shared_ptr<Button> playButton = make_shared<Button>(ui);
    MainMenuScene(UISystem* ui, SceneManager &sm):SceneBase(&sm), ui{ui}{}
    void setup() override;
    void setGameScene(unique_ptr<SceneBase> scene){gameScene.swap(scene);}

    private:
    sf::Vector2f playPos;
    sf::Vector2f settingsPos;
    unique_ptr<SceneBase> gameScene = nullptr;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
        SceneBase::draw(target, state);
        target.draw(*playButton.get());
        target.draw(playLabel);
        target.draw(settingsLabel);
        target.draw(mainMenuLabel);
    };

    virtual void cleanup() override{
        cout << "MainMenuScene: Running cleanup (currently does nothing)\n";
    }

    void loadPlaySceneButtonCallback(){
        if (gameScene){
            sceneManager->loadScene(std::move(gameScene));
        }
    }
};