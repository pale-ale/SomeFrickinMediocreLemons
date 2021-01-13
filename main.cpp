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


    //auto myCard = Fireball();
    auto myCard2 = Fireball();
    b.AddCard(myCard2, false);
    b.RemoveCard(0, false);
    //card myCard2 = card();
    auto myPlayer = Player();
    mainGame.addPlayer(&myPlayer);

	myPlayer.addCardToDeck(&myCard2);
    //myPlayer.addCardToDeck(&myCard);
    myPlayer.drawCards(1);

    sf::RenderWindow window(sf::VideoMode(
        Settings::defaultWidth, 
        Settings::defaultHeight), 
        "Nothing works!!",
        sf::Style::Default
        );
    window.setKeyRepeatEnabled(false);
    auto ui = UISystem(&window);
    ui.addChild(&(myCard2.cardButton));
    window.setSize({(uint)(Settings::defaultWidth*scale), (uint)(Settings::defaultHeight*scale)});
    window.setVerticalSyncEnabled(true);
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
