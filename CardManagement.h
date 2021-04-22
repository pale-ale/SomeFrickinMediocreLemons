#pragma once

#include <iostream>
#include <memory>

class Card;
class UISystem;

class Fireball;
class Kalle;
class Vinesnatcher;

namespace CardTypes{
	enum CardType{
		MagicCard,
		MonsterCard,
	};

	enum Cards{
		Fireball,
		//Kalle,
		Vinesnatcher,
		MAX
	};
};

class CardSpawner{
	public:
	static std::shared_ptr<Card> SpawnCard(UISystem *ui, CardTypes::Cards card);
	static std::shared_ptr<Card> SpawnCardRandom(UISystem *ui);
};