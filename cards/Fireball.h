#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Card.h"

template <typename ...T>
class IEventCallback;
class Player;

using std::cout;

class Fireball : public Card{
	public:
	Fireball(UISystem* ui);
	inline static const string pathToImage = "/usr/share/test/resources/Fireball.png";
    inline static const string description = "Deals 10 damage directly to the leader";
	static constexpr FMana cost = FMana({0,0,0,1,0});
	virtual void setupButtonBinding() override;
	virtual void onCardClicked() override;
	virtual void setupActions(){}
};
