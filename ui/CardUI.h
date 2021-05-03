#include <SFML/Graphics.hpp>

#include "../Card.h"
#include "Button.h"
#include "CardPreview.h"
#include "../GlobalFunctions.h"
#include "../IDragAndDroppable.h"

#include "UIElement.h"

class Button;
template <typename ...T>
class IEventCallback;
class TextBox;
class Battlefield;
class CardPreview;

class CardUI : public UIElement, public IDragAndDroppable{
    public:
    CardUI(UISystem *ui, Card *owningCard);
    ~CardUI();

    void setPosition(const sf::Vector2f &newPosition) override;
    void setRotation(const float &newRotation) override;
    void initializeSubComponents() override;
    void updateCardImage();
    void updateCardStatDisplay();

    virtual void OnDragMove(const sf::Vector2f &newPos) override;
	virtual void OnDragStart() override;
	virtual void OnDragEnd() override;

	virtual void onCardClicked();
	virtual void onCardBeginMouseover();
	virtual void onCardEndMouseover();
     
    virtual void setSnapPoints(const vector<sf::Vector2f> &points){snapPoints = points;}

    Card *getCard(){ return owningCard; }
	std::shared_ptr<Button> cardButton;

private:
	int snapPointIndex = -1;
    Card *owningCard = nullptr;
    std::shared_ptr<CardPreview> preview = nullptr;

    const sf::Vector2f cardDimensions = {Settings::cardSizeX, Settings::cardSizeY};
    const sf::Vector2f imageDimensions = {1200, 900};
	const sf::Vector2f imageOffset = {0, -13};
    const sf::Vector2f labelCenterOffset = {0, -35};
    const sf::Vector2f hpStatOffset = {-20, -40};
	const sf::Vector2f powerStatOffset = {10, -40};
	const sf::Vector2f descOffset = {-20, 10};

	vector<sf::Vector2f> snapPoints;
    sf::Sprite imageSprite;
    sf::Sprite borderSprite;

    sf::Text cardLabel;
    sf::Text hpStatDisplay;
	sf::Text powerStatDisplay;
    std::shared_ptr<TextBox> cardDescription;

	std::shared_ptr<sf::Texture> imageTexture = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> borderBackTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> borderFrontTexture = std::make_shared<sf::Texture>();

    std::shared_ptr<sf::Font> font = std::make_unique<sf::Font>();
    const std::shared_ptr<sf::Texture> getTexture() const {return imageTexture;}
    
	sf::Vector2f scaleVectorSettings(const sf::Vector2f &v){
		return {v.x*Settings::cardScaleX, v.y*Settings::cardScaleY};
	}


protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};