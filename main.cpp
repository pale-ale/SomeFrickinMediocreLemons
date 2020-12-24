#include <SFML/Graphics.hpp>
 
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    auto font = sf::Font();
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf");
    auto sometext = sf::Text();
    sometext.setString("test");
    sometext.setFont(font);
 
    shape.setFillColor(sf::Color::Green);
 
    while (window.isOpen())
    {
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
