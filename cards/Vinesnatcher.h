#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Card.h"
#include "../CardSelectionInfo.h"
#include "../Player.h"
#include "../ui/MultiSelect.h"

using std::cout;

class CardSelector;
class Battlefield;

class Vinesnatcher : public card{
	public:
	inline static const string pathToImage = "Vinesnatcher.png";
    inline static const string description = "Select a card to deal 2 damage to it.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher(UISystem* ui);
	virtual void play() override;
	virtual void onCardBeginMouseover() override;
	virtual void onReceiveSelection(list<card*> cards) override;
	virtual void onCardDeath() override;

	virtual void setupButtonBinding() override {
		cardButton->onClickCallback = std::make_shared<EventCallback<card>>(this, &card::onCardClicked);
		cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::onCardBeginMouseover);
		cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<card>>(this, &card::onCardEndMouseover);
		cardButton->onDragMoveCallback = std::make_shared<EventCallback<card, const sf::Vector2f&>>(this, &card::OnDragMove);
		cardButton->onDragEndCallback = std::make_shared<EventCallback<card>>(this, &card::OnDragEnd);
		cardButton->onDragStartCallback = std::make_shared<EventCallback<card>>(this, &card::OnDragStart);
	}
	void tapOptionCallback(){cout << "tap?\n";}
	void attackOptionCallback(){cout << "attack!\n";}
	virtual void tap() override;
	shared_ptr<MultiSelect> multiSelector;

};
