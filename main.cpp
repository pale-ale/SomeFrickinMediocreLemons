#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "KeyboardDelegate.h"
#include <vector>
#include "Player.h"
#include "Game.h"
#include "cards/fireball.h"

using namespace std;


void OnSpace(sf::Event event){
    cout << "I've been called! Key: " << event.key.code << " Pressed: " << (event.type == event.KeyPressed) << endl;
}

int main()
{
    auto delegateHandler = KeyboardDelegateManager();
    auto mainGame = Game();
    auto spaceDelegate = Delegate();
    spaceDelegate.Bind(new function<void(sf::Event)>(OnSpace));
    delegateHandler.SetupDelegateKeyBinding(spaceDelegate, sf::Keyboard::Space);

    //card myCard = card(cardType::MonsterCard, "testname", sf::Vector2<float>(0,0));
    card myCard2 = Fireball();
    //card myCard2 = card();
    auto myPlayer = Player();
    mainGame.addPlayer(&myPlayer);

	myPlayer.addCardToDeck(&myCard2);
    //myPlayer.addCardToDeck(&myCard);
    myPlayer.drawCards(1);

    sf::RenderWindow window(sf::VideoMode(400, 240), "SFML works!");
    window.setKeyRepeatEnabled(false);

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
        events.clear();
        window.clear();
      
        window.draw(mainGame);
        window.display();
    }
    return 0;
}
