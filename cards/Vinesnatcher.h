#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Card.h"
#include "../CardSelectionInfo.h"
#include "../Player.h"
#include "../ui/MultiSelect.h"
#include "../actions/VinesnatcherTap.h"

using std::cout;

class CardSelector;
class Battlefield;

class Vinesnatcher : public Card{
	public:
	inline static const string pathToImage = "Vinesnatcher.png";
    inline static const string description = "Select a card to deal 2 damage to it.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher(UISystem* ui);
	virtual void onCardDeath() override;
	virtual void setupActions() override{
		actions.push_back(make_shared<DefaultAttack>(owner, this));
		actions.push_back(make_shared<VinesnatcherTap>(owner, this));
	}
	virtual void setOwner(Player *newOwner){
		Card::setOwner(newOwner);
		for (auto &action : actions){
			action->setOwningPlayer(newOwner);
		}
	}

	virtual void setupButtonBinding() override {
		cardButton->onClickCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardClicked);
		cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Vinesnatcher>>(this, &Vinesnatcher::onCardBeginMouseover);
		cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(this, &Card::onCardEndMouseover);
		cardButton->onDragMoveCallback = std::make_shared<EventCallback<Card, const sf::Vector2f&>>(this, &Card::OnDragMove);
		cardButton->onDragEndCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragEnd);
		cardButton->onDragStartCallback = std::make_shared<EventCallback<Card>>(this, &Card::OnDragStart);
	}
};
