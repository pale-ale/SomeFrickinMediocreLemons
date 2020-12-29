#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class card : public sf::Drawable{
	public:
	card(string Type, string Name, sf::Vector2f Position);
	string returnType();
	string getType();
	void moveGraveyard();
	bool checkGraveyard();
	void setPosition(sf::Vector2f newPosition);
	string getName();
	void setFlipState(bool frontFaceUp);
	bool getFlipped();

	private:
	bool frontFaceUp;
	bool graveyard;
	string type;
	string name;
	sf::Vector2f position;
	sf::Texture cardBackTexture;
	sf::Texture cardFrontTexture;
	sf::Sprite cardSprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {	
        target.draw(cardSprite, states);
    }
};
