#pragma once

#include <SFML/Graphics.hpp>

#include "../Card.h"

class Battlefield;

class Vinesnatcher : public Card{
	public:
	Vinesnatcher(UISystem *ui = nullptr);
	inline static const string pathToImage = "Vinesnatcher.png";
    inline static const string description = "This is the Vinesnatcher's description.";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	virtual void onCardDeath() override;
	virtual void setupActions() override;
};
