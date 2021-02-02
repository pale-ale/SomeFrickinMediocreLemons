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
#include "Battlefield.h"
#include "Settings.h"

using namespace std;


int main()
{
    auto delegateHandler = KeyboardDelegateManager();
    auto mainGame = Game();
    auto spaceDelegate = Delegate();
    auto b = Battlefield();
    float scale = 2;

    vector<card*> cards;
    for (int i=0; i<8; i++){
        auto fb = new Fireball();
        fb->setName("Card" + std::to_string(i));
        cards.push_back(fb);
    }
  
    auto myPlayer = Player();
    mainGame.addPlayer(&myPlayer);

    sf::RenderWindow window(sf::VideoMode(
        Settings::defaultWidth, 
        Settings::defaultHeight), 
        "Nothing works!!",
        sf::Style::Default
        );
    window.setKeyRepeatEnabled(false);
    auto ui = UISystem(&window);
    window.setSize({(uint)(Settings::defaultWidth*scale), (uint)(Settings::defaultHeight*scale)});
    window.setVerticalSyncEnabled(true);

    for (int i=0; i<cards.size(); i++){
	    myPlayer.addCardToDeck(cards[i]);
        ui.addListener(&(cards[i]->cardButton));
    }
	
    myPlayer.drawCards(5);
    myPlayer.printHand();

    vector<sf::Event> events;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time tickDelay = clock.getElapsedTime();
        clock.restart();
        
        //myPlayer.setRotation(myPlayer.getRotation() + 0.1 * tickDelay.asMilliseconds());
        
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
