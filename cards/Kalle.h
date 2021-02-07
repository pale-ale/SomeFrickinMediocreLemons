#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using std::cout;

class Kalle : public card{
	public:
	inline static const string pathToImage = "/usr/share/test/resources/Kalle.png";
    inline static const string description = "Doppelklang!";
	static constexpr FMana cost = FMana({0,0,20,0,0});
	Kalle();
	
	virtual void Play() override;

	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::OnCardClicked);
	}
};