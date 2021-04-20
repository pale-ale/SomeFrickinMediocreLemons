#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Card.h"

using std::cout;

class Battlefield;
class CardSelector;
class CardSelectionInfo;

class Vinesnatcher : public Card{
	public:
	inline static const string pathToImage = "Vinesnatcher.png";
    inline static const string description = "Select a card to deal 2 damage to it.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher(UISystem* ui);
	virtual void onCardDeath() override;
	virtual void setupActions() override;
	

	virtual void setupButtonBinding() override;
};
