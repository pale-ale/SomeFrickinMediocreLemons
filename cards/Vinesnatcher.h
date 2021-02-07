#include <SFML/Graphics.hpp>
#include <iostream>
#include "../card.h"
#include "../Player.h"

using std::cout;

class Vinesnatcher : public card{
	public:
	inline static const string pathToImage = "/usr/share/test/resources/Vinesnatcher.png";
    inline static const string description = "A fireball that\nattacks enemies";
	static constexpr FMana cost = FMana({0,0,1,0,0});

	Vinesnatcher();
	virtual void Play() override;
	
	virtual void SetupButtonBinding() override {
		cardButton.callback = new EventCallback<card>(this, &card::OnCardClicked);
	}
};
