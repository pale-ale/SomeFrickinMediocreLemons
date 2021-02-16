#include "Battlefield.h"
#include "cards/Fireball.h"
#include "cards/Kalle.h"
#include "cards/Vinesnatcher.h"
#include "Events/EventCallback.h"
#include "Game.h"
#include <iostream>
#include "KeyboardDelegate.h"
#include "Player.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Bar.h"
#include "UI/Button.h"
#include "UI/UISystem.h"
#include <vector>
#include "math.h"

using std::cout;
using std::endl;

int main()
{
    sf::RenderWindow window(sf::VideoMode(
        Settings::defaultWidth, 
        Settings::defaultHeight), 
        "Nothing works!!",
        sf::Style::Default
        );
    auto delegateHandler = KeyboardDelegateManager();
    auto mainGame = Game();
    auto spaceDelegate = Delegate();
    auto ui = UISystem(&window);
    float scale = 2;
    window.setKeyRepeatEnabled(false);
    window.setSize({(uint)(Settings::defaultWidth*scale), (uint)(Settings::defaultHeight*scale)});
    window.setVerticalSyncEnabled(true);

    vector<card*> player0Cards;
    for (int i=0; i<5; i++){
        auto fb = new Vinesnatcher(&ui);
        fb->setName("p1Card" + std::to_string(i));
        player0Cards.push_back(fb);
    }
    vector<card*> player1Cards;
    for (int i=0; i<5; i++){
        auto fb = new Vinesnatcher(&ui);
        fb->setName("p1Card" + std::to_string(i));
        player1Cards.push_back(fb);
    }
  
    auto player0 = Player(&ui, "Player0");
    auto player1 = Player(&ui, "Player1");
    mainGame.addPlayer(&player0);
    mainGame.addPlayer(&player1);
    
    for (int i=0; i<player0Cards.size(); i++){
	    player0.addCardToDeck(player0Cards[i]);
        ui.addListener(&(player0Cards[i]->cardButton));
    }
    for (int i=0; i<player1Cards.size(); i++){
	    player1.addCardToDeck(player1Cards[i]);
        ui.addListener(&(player1Cards[i]->cardButton));
    }
	
    player0.drawCards(5);
    player0.printHand();
    player1.drawCards(5);
    player1.printHand();

    vector<sf::Event> events;
    sf::Clock clock;
    mainGame.startTurnOfNextPlayer();

    while (window.isOpen())
    {
        sf::Time tickDelay = clock.getElapsedTime();
        clock.restart();
        
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
        window.getPosition();
        window.draw(mainGame);
        window.draw(ui);
        window.display();
    }
    return 0;
}
