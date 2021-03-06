#include <SFML/Graphics.hpp>

#include "../Card.h"

class FireballPlay;
template <typename ...T>
class IEventCallback;
class Player;

using std::cout;

class Fireball : public Card{
	public:
	Fireball(UISystem *ui = nullptr);
	inline static const string pathToImage = "Fireball.png";
    inline static const string description = "Your average, ubiquitous fireball.";
	static constexpr FMana cost = FMana({0,0,0,2,0});
	virtual void play() override;
	virtual void setupActions() override;
};
