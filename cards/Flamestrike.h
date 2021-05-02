#include <SFML/Graphics.hpp>

#include "../Card.h"

class FireballPlay;
template <typename ...T>
class IEventCallback;
class Player;

using std::cout;

class Flamestrike : public Card{
	public:
	Flamestrike(UISystem *ui = nullptr);
	inline static const string pathToImage = "Flamestrike.png";
    inline static const string description = "\"I beat the wall of flame with a yo-yo!\"";
	static constexpr FMana cost = FMana({0,0,0,1,0});
	virtual void play() override;
	virtual void setupActions() override;
};
