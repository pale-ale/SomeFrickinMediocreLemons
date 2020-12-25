#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include "KeyboardDelegate.h"
#include <vector>

using namespace std;


void DoesNothingButPrint(){
    cout << "Test" << endl;
}
 
int main()
{
    auto delegateHandler = KeyboardDelegateManager();
    auto delegate = Delegate();
    delegate.Bind(new function<void()>(DoesNothingButPrint));
    delegateHandler.SetupDelegateKeyBinding(delegate, sf::Keyboard::Space);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    auto font = sf::Font();
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf");
    auto sometext = sf::Text();  
    sometext.setString("I Am A String");
    sometext.setFont(font);
 
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        delegateHandler.Tick();

        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(sometext);
        window.display();
    }
    return 0;
}
