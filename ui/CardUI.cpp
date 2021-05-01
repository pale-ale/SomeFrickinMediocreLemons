#include "CardUI.h"
#include "TextBox.h"


CardUI::CardUI(UISystem *ui, Card *owningCard) : UIElement(ui), owningCard{owningCard},
cardDescription{make_shared<TextBox>(ui)},
cardButton{make_shared<Button>(ui, sf::Color{0, 0, 0, 0}, sf::Color{0, 0, 0, 0})}
{
    imageSprite.setScale(Settings::cardScale * 0.0335f);
    imageSprite.setOrigin(imageDimensions / 2.0f);
    borderBackTexture->loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardBack);
    borderFrontTexture->loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardFront);
    borderSprite.setTexture(*borderFrontTexture);
    borderSprite.setScale(Settings::cardScale);
    borderSprite.setOrigin(Settings::cardSize / 2.0f);
    updateCardImage();
   	font->loadFromFile(Settings::validFontPath);
    cardLabel.setFont(*font);
	cardLabel.setFillColor(Settings::blackColor);
	cardLabel.setScale(scaleVectorSettings({0.3, 0.3}));
    cardLabel.setString(owningCard->label);
	cardLabel.setOrigin(sf::Vector2f{cardLabel.getLocalBounds().width, cardLabel.getLocalBounds().height} * .5f);
	cardDescription->setContent(owningCard->description);
	cardDescription->setScale(Settings::cardScale.x * 0.17, Settings::cardScale.y * 0.17);
	cardDescription->setSize(Settings::cardSize + descOffset);
    hpStatDisplay.setFont(*font);
	hpStatDisplay.setFillColor(Settings::redColor);
	hpStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
	powerStatDisplay.setFont(*font);
	powerStatDisplay.setFillColor(Settings::blackColor);
	powerStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
    updateCardStatDisplay();
    cardButton->isDragable = true;
	cardButton->setName(name + "Button");
	cardButton->setScale(Settings::cardScale.x, Settings::cardScale.y);
  	cardButton->onClickCallback = std::make_shared<EventCallback<Card>>(owningCard, &Card::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<Card>>(owningCard, &Card::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<Card>>(owningCard, &Card::onCardEndMouseover);
    cardButton->onDragMoveCallback = std::make_shared<EventCallback<Card, const sf::Vector2f&>>(owningCard, &Card::OnDragMove);
    cardButton->onDragEndCallback = std::make_shared<EventCallback<Card>>(owningCard, &Card::OnDragEnd);
    cardButton->onDragStartCallback = std::make_shared<EventCallback<Card>>(owningCard, &Card::OnDragStart);
}

void CardUI::setPosition(const sf::Vector2f &newPosition){
    UIElement::setPosition(newPosition);
    imageSprite.setPosition(newPosition + scaleVectorSettings(imageOffset));
    borderSprite.setPosition(newPosition);
    cardButton->setPosition(newPosition);
	cardDescription->setPosition(newPosition + scaleVectorSettings(descOffset));
	hpStatDisplay.setPosition(newPosition + scaleVectorSettings(hpStatOffset));
	powerStatDisplay.setPosition(newPosition + scaleVectorSettings(powerStatOffset));
	cardLabel.setPosition(newPosition + scaleVectorSettings(labelCenterOffset));
}

void CardUI::setRotation(const float &newRotation){
    UIElement::setRotation(newRotation);
    auto t = sf::Transform().rotate(newRotation).scale(Settings::cardScale);
    imageSprite.setRotation(newRotation);
    imageSprite.setPosition(getPosition() + t.transformPoint(imageOffset));
    borderSprite.setRotation(newRotation);
    cardButton->setRotation(newRotation);
	cardDescription->setRotation(newRotation);
	cardDescription->setPosition(getPosition() + t.transformPoint(descOffset));
	hpStatDisplay.setRotation(newRotation);
	hpStatDisplay.setPosition(getPosition() + t.transformPoint(hpStatOffset));
	powerStatDisplay.setRotation(newRotation);
	powerStatDisplay.setPosition(getPosition() + t.transformPoint(powerStatOffset));
	cardLabel.setRotation(newRotation);
	cardLabel.setPosition(getPosition() + t.transformPoint(labelCenterOffset));
}

void CardUI::updateCardImage(){
    imageTexture = std::make_shared<sf::Texture>();
    cout << owningCard->pathToImage << endl;
    if (!imageTexture->loadFromFile(owningCard->pathToImage))
    {
        cout << "CardUI: Error loading image at \'" << owningCard->pathToImage << "'. Trying the default.\n";
        auto newPath = string(Settings::programDir) + Settings::relativeAssetCardPath + "/Unknown.png";
        imageTexture->loadFromFile(newPath);
    };
    imageSprite.setTexture(*imageTexture);
}

void CardUI::updateCardStatDisplay()
{
	hpStatDisplay.setString(to_string(owningCard->getHealth()));
	powerStatDisplay.setString(to_string(owningCard->getPower()));
}

void CardUI::initializeSubComponents()
{
	UIElement::initializeSubComponents();
	cardButton->initializeSubComponents();
}

void CardUI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(borderSprite, states);
    if (owningCard->getFlipState()){
        target.draw(imageSprite, states);
        target.draw(cardLabel, states);
        target.draw(*cardDescription, states);
        target.draw(hpStatDisplay, states);
        target.draw(powerStatDisplay, states);
        target.draw(*cardButton, states);
    }
}
