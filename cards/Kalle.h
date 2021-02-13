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
	Kalle();
	
	virtual void Play() override;
	virtual void OnCardBeginMouseover() override;
	virtual void SetupButtonBinding() override {
		cardButton.onClickCallback = new EventCallback<card>(this, &card::OnCardClicked);
		cardButton.onBeginMouseoverCallback = new EventCallback<Kalle>(this, &Kalle::OnCardBeginMouseover);
		cardButton.onEndMouseoverCallback = new EventCallback<card>(this, &card::OnCardEndMouseover);
	}
};