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


    auto myCard1 = Fireball();
    auto myCard2 = Fireball();
	auto myCard3 = Fireball();
	auto myCard4 = Fireball();
	auto myCard5 = Fireball();
	auto myCard6 = Fireball();
	auto myCard7 = Fireball();
	auto myCard8 = Fireball();
  
    auto myPlayer = Player();
    mainGame.addPlayer(&myPlayer);

	myPlayer.addCardToDeck(&myCard1);
	myPlayer.addCardToDeck(&myCard2);
	myPlayer.addCardToDeck(&myCard3);
	myPlayer.addCardToDeck(&myCard4);
	myPlayer.addCardToDeck(&myCard5);
	myPlayer.addCardToDeck(&myCard6);
	myPlayer.addCardToDeck(&myCard7);
	myPlayer.addCardToDeck(&myCard8);

    myPlayer.drawCards(7);
    myPlayer.printHand();

    myCard1.SetPosition(sf::Vector2f(50,50));
    myCard1.SetRotation(90);

    //myPlayer.SetRotation(0);
    //myCard2.SetRotation(180);
    //cout << myPlayer.GetRotation() << endl;

    sf::RenderWindow window(sf::VideoMode(
        Settings::defaultWidth, 
        Settings::defaultHeight), 
        "Nothing works!!",
        sf::Style::Default
        );
    window.setKeyRepeatEnabled(false);
    auto ui = UISystem(&window);
    ui.addChild(&(myCard3.cardButton));
    window.setSize({(uint)(Settings::defaultWidth*scale), (uint)(Settings::defaultHeight*scale)});
    window.setVerticalSyncEnabled(true);
    vector<sf::Event> events;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time tickDelay = clock.getElapsedTime();
        clock.restart();
        if (&myCard4){
            myCard4.SetRotation((int)(myCard4.GetRotation() + 0.2 * tickDelay.asMilliseconds()) % 360);
        }
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
