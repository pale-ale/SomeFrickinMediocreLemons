#include "Scene.h"
#include "Game.h"
#include <iostream>
#include "cards/Vinesnatcher.h"

using std::cout;

class GameScene : public SceneBase{
    public:
    GameScene(UISystem* ui, SceneManager &sm):
        SceneBase(&sm),
        player0{std::make_shared<Player>(ui, "Player0")}, 
        player1{std::make_shared<Player>(ui, "Player1")},
        ui{ui}{}
    Game mainGame = Game();
    UISystem* ui;
    std::shared_ptr<Player> player0;
    std::shared_ptr<Player> player1;
    void setup() override {
        player0->initializeSubComponents();
        player1->initializeSubComponents();

        for (int i=0; i<5; i++){
            auto fb = std::make_shared<Vinesnatcher>(ui);
            fb->initializeSubComponents();
            fb->setName("p0Card" + std::to_string(i));
            player0->addCardToDeck(fb);
        }
        for (int i=0; i<5; i++){
            auto fb = std::make_shared<Vinesnatcher>(ui);
            fb->initializeSubComponents();
            fb->setName("p1Card" + std::to_string(i));
            player1->addCardToDeck(fb);
        }

        mainGame.addPlayer(player0.get());
        mainGame.addPlayer(player1.get());
        
        player0->drawCards(3);
        player0->printHand();
        player1->drawCards(3);
        player1->printHand();

        mainGame.startTurnOfNextPlayer();
    }

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(mainGame);
    }
};