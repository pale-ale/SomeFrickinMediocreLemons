#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Card.h"
#include "../Player.h"

using std::cout;

class Fireball : public card{
	public:
	Fireball(UISystem* ui);
	inline static const string pathToImage = "/usr/share/test/resources/Fireball.png";
    inline static const string description = "A fireball that\nattacks enemies";
	static constexpr FMana cost = FMana({0,0,0,1,0});
	virtual void play() override;
	virtual void onCardBeginMouseover() override;
	virtual void setupButtonBinding() override {
		cardButton->onMouseDownCallback = std::make_shared<EventCallback<card>>(this, &card::onCardClicked);
		cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Fireball>>(this, &Fireball::onCardBeginMouseover);
		cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<card>>(this, &card::onCardEndMouseover);
	}
};
