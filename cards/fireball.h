#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"

using namespace std;

class fireball : public card::card{
	public:
	virtual bool starteffect(card *card) override;
	private:
	sf::Texture descriptiveImage;
};
