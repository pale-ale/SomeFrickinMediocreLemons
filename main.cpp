#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "KeyboardDelegate.h"
#include <vector>
#include "Player.h"

using namespace std;


void OnSpace(sf::Event event){
    cout << "I've been called! Key: " << event.key.code << " Pressed: " << (event.type == event.KeyPressed) << endl;
}
 
int main()
{
    auto delegateHandler = KeyboardDelegateManager();
    auto spaceDelegate = Delegate();
    spaceDelegate.Bind(new function<void(sf::Event)>(OnSpace));
    delegateHandler.SetupDelegateKeyBinding(spaceDelegate, sf::Keyboard::Space);
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    auto font = sf::Font();
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf");
    auto sometext = sf::Text();  
    sometext.setString("I Am A String");
    sometext.setFont(font);
 
    shape.setFillColor(sf::Color::Green);
    vector<sf::Event> events;
    window.setKeyRepeatEnabled(false);

    auto player = Player();
    auto mageCard = card("Human", "Battle Mage");
    auto SSG08er = card("Human", "Nico der Scharfschütze");
    player.addCardToDeck(mageCard);
    player.addCardToDeck(SSG08er);
    player.printDeck();
    player.drawCards(2);
    player.printDeck();
    player.printHand();
    const auto playerHand = player.getHand();
    cout << playerHand->size() << endl;
    player.playCard(*playerHand->begin());
    player.playCard(*playerHand->begin());
    player.printHand();
    cout << "Success" << endl;
    
    exit(0);

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
        window.draw(shape);
        window.draw(sometext);
        window.display();
    }
    return 0;
}
