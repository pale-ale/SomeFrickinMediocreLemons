#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "KeyboardDelegate.h"
#include <vector>
#include "Player.h"
#include "Game.h"
#include "cards/fireball.h"
#include "UI/UISystem.h"
#include "UI/Button.h"
#include "Events/EventCallback.h"

using namespace std;

int main()
{
    auto delegateHandler = KeyboardDelegateManager();
    auto mainGame = Game();
    auto spaceDelegate = Delegate();

    //card myCard = card(cardType::MonsterCard, "testname", sf::Vector2<float>(0,0));
    auto myCard2 = Fireball();
    //card myCard2 = card();
    auto myPlayer = Player();
    mainGame.addPlayer(&myPlayer);

	myPlayer.addCardToDeck(&myCard2);
    //myPlayer.addCardToDeck(&myCard);
    myPlayer.drawCards(1);

    sf::RenderWindow window(sf::VideoMode(400, 240), "SFML!");
    window.setKeyRepeatEnabled(false);
    auto ui = UISystem(&window);
    ui.addChild(&(myCard2.cardButton));

    vector<sf::Event> events;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            events.push_back(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        delegateHandler.Tick(events);
        ui.processEvents(events);
        events.clear();
        window.clear();
      
        window.draw(mainGame);
        window.draw(ui);
        window.display();
    }
    return 0;
}
