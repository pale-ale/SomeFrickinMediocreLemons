#include "Scene.h"
#include "UI/UISystem.h"
#include "SFML/Graphics.hpp"
#include "UI/Button.h"

class MainMenuScene: public SceneBase{
    UISystem* ui;
    public:
    sf::Font font;
    sf::Text mainMenuLabel;
    sf::Text playLabel;
    sf::Text settingsLabel;
    Button playButton = Button(ui);
    MainMenuScene(UISystem* ui, SceneManager &sm):SceneBase(&sm), ui{ui}{}
    void setup() override;
    void setGameScene(SceneBase* gameScene){this->gameScene = gameScene;}

    private:
    sf::Vector2f playPos;
    sf::Vector2f settingsPos;
    SceneBase* gameScene = nullptr;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override {
        SceneBase::draw(target, state);
        target.draw(playButton);
        target.draw(playLabel);
        target.draw(settingsLabel);
        target.draw(mainMenuLabel);
    };

    virtual void cleanup() override{
        cout << "cleaning up...\n";
    }

    void loadPlaySceneButtonCallback(){
        cout << "test\n";
        if (gameScene){
            sceneManager->loadScene(gameScene);
        }
    }
};