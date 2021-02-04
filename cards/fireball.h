#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using namespace std;

class Fireball : public card{
	public:
	Fireball();
	virtual void Play() override {
		
	}
	virtual void OnCardClicked() override {
		cout << "i was clicked\n";
		if (cardLocation == hand && owner->bIsMyTurn){
			card::Play();
			cout << "...and playerd!\n";
		}
	}
	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::OnCardClicked);
	}
};
