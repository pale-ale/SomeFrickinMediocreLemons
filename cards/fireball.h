#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"

using namespace std;

class Fireball : public card{
	public:
	Fireball();
	virtual void Play() override {cout << "*Epic Fireball FX!*\n";}
	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::Play);
	}
};
