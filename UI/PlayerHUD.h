#include "../Settings.h"
#include "UISystem.h"
#include "CardPreview.h"

class card;

class PlayerHUD : public UIElement
{
public:
    PlayerHUD(UISystem* parent);
    void setDeckCount(int deckCount);
    void setHandCount(int handCount);
    virtual void setPosition(sf::Vector2f newPosition) override;
    void generatePreview(std::shared_ptr<const card> &cardToPreview);
    void removePreview();

private:
    sf::Text deckCountText;
    sf::Text handCountText;
    sf::Vector2f deckTextOffset = {-170, -50};
    sf::Vector2f handTextOffset = {-10, -35};
    sf::Vector2f cardPreviewOffset = {0, -100};
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    std::shared_ptr<CardPreview> cardPreview;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        UIElement::draw(target, state);
        target.draw(deckCountText);
        target.draw(handCountText);
    }
};