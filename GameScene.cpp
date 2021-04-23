#include "GameScene.h"
#include "Player.h"
#include "Card.h"

#include "CardManagement.h"

GameScene::GameScene(UISystem* ui, SceneManager &sm):
        SceneBase(&sm),
        player0{std::make_shared<Player>(ui, "Player0")}, 
        player1{std::make_shared<Player>(ui, "Player1")},
        ui{ui}{}

void GameScene::setup()
{
    player0->initializeSubComponents();
    player1->initializeSubComponents();

    for (int i = 0; i < 10; i++)
    {
        auto fb = CardSpawner::SpawnCardRandom(ui);
        fb->initializeSubComponents();
        fb->setName("p0Card" + std::to_string(i));
        player0->addCardToDeck(fb);
    }
    for (int i = 0; i < 10; i++)
    {
        auto fb = CardSpawner::SpawnCardRandom(ui);
        fb->initializeSubComponents();
        fb->setName("p1Card" + std::to_string(i));
        player1->addCardToDeck(fb);
    }

    mainGame.addPlayer(player0.get());
    mainGame.addPlayer(player1.get());

    player0->drawCards(7);
    player0->printHand();
    player1->drawCards(7);
    player1->printHand();

    mainGame.startTurnOfNextPlayer();
}
