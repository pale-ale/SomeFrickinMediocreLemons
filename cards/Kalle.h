#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using namespace std;

class Kalle : public card{
	public:
	Kalle();
	virtual void Play() override {
		
	}
	virtual void OnCardClicked() override {
		cout << "i was clicked\n";
		if (cardLocation == hand && owner->bIsMyTurn){
			card::Play();
			cout << "...and playerd!\n";
            cout << "Player has currently "<< owner->LifePoints<< endl;
            owner->LifePoints += 2000;
            cout << "Player has currently "<< owner->LifePoints<< endl;
		}
        
	}
	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::OnCardClicked);
	}
};