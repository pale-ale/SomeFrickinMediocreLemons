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

	Vinesnatcher(UISystem* ui);
	virtual void play() override;
	virtual void onCardBeginMouseover() override;

	virtual void setupButtonBinding() override {
		cardButton.onMouseDownCallback = new EventCallback<card>(this, &card::onCardClicked);
		cardButton.onBeginMouseoverCallback = new EventCallback<Vinesnatcher>(this, &Vinesnatcher::onCardBeginMouseover);
		cardButton.onEndMouseoverCallback = new EventCallback<card>(this, &card::onCardEndMouseover);
	}

	virtual void tap() override{
		auto ownerSelection = owner->cardSelector.getSelectedCards();
		owner->cardSelector.resetSelection();
		cout << "vinesnatcher tapped.\n";
		if (ownerSelection.size() == 0){
			owner->startSelection();
			owner->awaitingSelection = this;
			return;
		}
		if (ownerSelection.size() == 1){
			auto card = *(ownerSelection.begin());
			cout << card->getName() << " gon get whipped.\n";
			card->owner->battlefield.removeCard(card);
			ownerSelection.clear();
		}
	}
};
