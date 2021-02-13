#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using std::cout;

class CardSelector;
class Battlefield;

class Vinesnatcher : public card{
	public:
	inline static const string pathToImage = "/usr/share/test/resources/Vinesnatcher.png";
    inline static const string description = "Select a card to oof it.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher();
	virtual void Play() override;
	virtual void OnCardBeginMouseover() override;

	virtual void SetupButtonBinding() override {
		cardButton.onClickCallback = new EventCallback<card>(this, &card::OnCardClicked);
		cardButton.onBeginMouseoverCallback = new EventCallback<Vinesnatcher>(this, &Vinesnatcher::OnCardBeginMouseover);
		cardButton.onEndMouseoverCallback = new EventCallback<card>(this, &card::OnCardEndMouseover);
	}
};
