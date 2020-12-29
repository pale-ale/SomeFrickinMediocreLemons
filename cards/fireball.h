#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class fireball : public card::card{
	public:
	virtual bool starteffect(card::card* card) const override;
	private:
	sf::Texture descriptiveImage
};
