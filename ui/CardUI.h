#include <SFML/Graphics.hpp>

#include "../Card.h"
#include "Button.h"
#include "UIElement.h"

class Button;
template <typename ...T>
class IEventCallback;
class TextBox;

class CardUI : public UIElement{
    public:
    CardUI(UISystem *ui, Card *owningCard);

    void setPosition(const sf::Vector2f &newPosition) override;
    void setRotation(const float &newRotation) override;
    void initializeSubComponents() override;
    void updateCardImage();
    void updateCardStatDisplay();
    
	std::shared_ptr<Button> cardButton;

    private:
    const std::shared_ptr<sf::Texture> getTexture() const {return imageTexture;}
    
    sf::Vector2f scaleVectorSettings(const sf::Vector2f &v){
		return {v.x*Settings::cardScale.x, v.y*Settings::cardScale.y};
	}

    Card *owningCard = nullptr;

    const sf::Vector2f imageDimensions = {1200, 900};
	const sf::Vector2f imageOffset = {0, -13};
    const sf::Vector2f labelCenterOffset = {0, -35};
    const sf::Vector2f hpStatOffset = {-20, -40};
	const sf::Vector2f powerStatOffset = {10, -40};
	const sf::Vector2f descOffset = {-20, 10};

	std::shared_ptr<sf::Texture> imageTexture = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> borderBackTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> borderFrontTexture = std::make_shared<sf::Texture>();

    std::shared_ptr<sf::Font> font = std::make_unique<sf::Font>();

    sf::Sprite imageSprite;
    sf::Sprite borderSprite;

    sf::Text cardLabel;
    sf::Text hpStatDisplay;
	sf::Text powerStatDisplay;
    std::shared_ptr<TextBox> cardDescription;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};