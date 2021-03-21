#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../CardSelectionInfo.h"
#include "../Player.h"

using std::cout;

class CardSelector;
class Battlefield;

class Vinesnatcher : public card{
	public:
	inline static const string pathToImage = "/usr/share/test/resources/Vinesnatcher.png";
    inline static const string description = "Select a card to deal 2 damage to it.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher(UISystem* ui);
	virtual void play() override;
	virtual void onCardBeginMouseover() override;
	virtual void onReceiveSelection(list<shared_ptr<card>> cards);

	virtual void setupButtonBinding() override {
		cardButton.onMouseDownCallback = new EventCallback<card>(this, &card::onCardClicked);
		cardButton.onBeginMouseoverCallback = new EventCallback<Vinesnatcher>(this, &Vinesnatcher::onCardBeginMouseover);
		cardButton.onEndMouseoverCallback = new EventCallback<card>(this, &card::onCardEndMouseover);
	}

	virtual void tap() override;
};
