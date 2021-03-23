#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using std::cout;

class Kalle : public card{
	public:
	inline static const string pathToImage = "/usr/share/test/resources/Kalle.png";
    inline static const string description = "Doppelklang!";
	inline static constexpr FMana cost{0,0,10,0,0};
	Kalle(UISystem* ui);
	
	virtual void play() override;
	virtual void onCardBeginMouseover() override;
	virtual void setupButtonBinding() override {
		cardButton.onMouseDownCallback = std::make_shared<EventCallback<card>>(this, &card::onCardClicked);
		cardButton.onBeginMouseoverCallback = std::make_shared<EventCallback<Kalle>>(this, &Kalle::onCardBeginMouseover);
		cardButton.onEndMouseoverCallback = std::make_shared<EventCallback<card>>(this, &card::onCardEndMouseover);
	}
};