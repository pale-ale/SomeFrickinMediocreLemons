#include <iostream>
#include <memory>

#include "Game.h"
#include "Scene.h"

using std::cout;

class Player;
class UISystem;

class GameScene : public SceneBase{
    public:
    GameScene(UISystem* ui, SceneManager &sm);
    Game mainGame = Game();
    UISystem* ui;
    std::shared_ptr<Player> player0 = nullptr;
    std::shared_ptr<Player> player1 = nullptr;
    void setup() override;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(mainGame);
    }
};