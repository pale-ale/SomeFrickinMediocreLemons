#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class card : public sf::Drawable{
	public:
	card(string Type, string Name, sf::Vector2<float> Position);
	string returnType();
	string getType();
	void moveGraveyard();
	bool checkGraveyard();
	string getName();

	private:
	bool graveyard;
	string type;
	string name;
	sf::Vector2<float> position;
	sf::Texture cardTexture;
	sf::Sprite cardSprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(cardSprite, states);
    }
};
