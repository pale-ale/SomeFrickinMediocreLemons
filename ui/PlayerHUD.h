#include "../Settings.h"
#include "UISystem.h"
#include "CardPreview.h"
#include "MultiSelect.h"

class card;

class PlayerHUD : public UIElement
{
public:
    PlayerHUD(UISystem* parent);
    void setDeckCount(int deckCount);
    void setHandCount(int handCount);
    virtual void setPosition(const sf::Vector2f &newPosition) override;
    void generatePreview(const card* cardToPreview);
    void removePreview();

private:
    sf::Text deckCountText;
    sf::Text handCountText;
    sf::Vector2f deckTextOffset = {-170, -50};
    sf::Vector2f handTextOffset = {-10, -35};
    sf::Vector2f cardPreviewOffset = {0, -100};
    sf::Vector2f cardActionShapeOffset = {280, 105};
    sf::Vector2f cardActionShapeDimensions = {100, 30};
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    std::shared_ptr<CardPreview> cardPreview;
    std::shared_ptr<MultiSelect> multiSelect;
    sf::RectangleShape cardActionShape;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override
    {
        target.draw(cardActionShape);
        target.draw(deckCountText);
        target.draw(handCountText);
        UIElement::draw(target, state);
    }
};