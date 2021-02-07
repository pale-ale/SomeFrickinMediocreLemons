#include "../Settings.h"
#include "UISystem.h"

class PlayerHUD : public UIElement{
    public:
    PlayerHUD();
    void setDeckCount(int deckCount);
    void setHandCount(int handCount);
    virtual void setPosition(sf::Vector2f newPosition) override;

    private:
    sf::Text deckCountText;
    sf::Text handCountText;
    sf::Vector2f deckTextOffset = {-170, -50};
    sf::Vector2f handTextOffset = {-10, -35};
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override{
        target.draw(deckCountText);
        target.draw(handCountText);
    }
    };