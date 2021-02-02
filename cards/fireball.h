#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"

using namespace std;

class Fireball : public card{
	public:
	Fireball();
	virtual void Play() override {
		card::Play();
		cout << "My name is \'" << name << "\'\n";
	}
	virtual bool OnMouseButtonDown() override {
		cout << "test\n";
		return false;
	}
	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::Play);
	}
};
