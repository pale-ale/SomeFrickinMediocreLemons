#include "CardUI.h"
#include "TextBox.h"
#include "../Player.h"
#include "../Battlefield.h"

CardUI::CardUI(UISystem *ui, Card *owningCard) : UIElement(ui), owningCard{owningCard}, 
cardDescription{make_shared<TextBox>(ui)},
cardButton{make_shared<Button>(ui, sf::Color{0, 0, 0, 0}, sf::Color{0, 0, 0, 0})}
{
	imageSprite.setScale(Settings::cardScaleX * 0.0335f, Settings::cardScaleY * 0.0335f);
    imageSprite.setOrigin(imageDimensions / 2.0f);
    borderBackTexture->loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardBack);
    borderFrontTexture->loadFromFile(string(Settings::programDir) + Settings::relativeAssetCardPath + Settings::relativeAssetCardFront);
    borderSprite.setTexture(*borderFrontTexture);
    borderSprite.setScale(Settings::cardScaleX, Settings::cardScaleY);
    borderSprite.setOrigin(Settings::cardSizeX * .5f, Settings::cardSizeY * .5f);
    updateCardImage();
   	font->loadFromFile(Settings::validFontPath);
    cardLabel.setFont(*font);
	cardLabel.setFillColor({0,0,0,255});
	cardLabel.setScale(scaleVectorSettings({0.3, 0.3}));
    cardLabel.setString(owningCard->label);
	cardLabel.setOrigin(sf::Vector2f{cardLabel.getLocalBounds().width, cardLabel.getLocalBounds().height} * .5f);
	cardDescription->setContent(owningCard->description);
	cardDescription->setScale(Settings::cardScaleX * 0.17, Settings::cardScaleY * 0.17);
	cardDescription->setSize(descOffset + sf::Vector2f{Settings::cardSizeX, Settings::cardSizeY});
    hpStatDisplay.setFont(*font);
	hpStatDisplay.setFillColor({255,0,0,255});
	hpStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
	powerStatDisplay.setFont(*font);
	powerStatDisplay.setFillColor({0,0,0,255});
	powerStatDisplay.setScale(scaleVectorSettings({0.5, 0.5}));
    updateCardStatDisplay();
    cardButton->isDragable = true;
	cardButton->setName(name + "Button");
	cardButton->setScale(Settings::cardScaleX, Settings::cardScaleY);
  	cardButton->onClickCallback = std::make_shared<EventCallback<CardUI>>(this, &CardUI::onCardClicked);
    cardButton->onBeginMouseoverCallback = std::make_shared<EventCallback<CardUI>>(this, &CardUI::onCardBeginMouseover);
    cardButton->onEndMouseoverCallback = std::make_shared<EventCallback<CardUI>>(this, &CardUI::onCardEndMouseover);
    cardButton->onDragMoveCallback = std::make_shared<EventCallback<CardUI, const sf::Vector2f&>>(this, &CardUI::OnDragMove);
    cardButton->onDragEndCallback = std::make_shared<EventCallback<CardUI>>(this, &CardUI::OnDragEnd);
    cardButton->onDragStartCallback = std::make_shared<EventCallback<CardUI>>(this, &CardUI::OnDragStart);
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
    auto t = sf::Transform().rotate(newRotation).scale(Settings::cardScaleX, Settings::cardScaleY);
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
    if (owningCard->bGetFlipState()){
        target.draw(imageSprite, states);
        target.draw(cardLabel, states);
        target.draw(*cardDescription, states);
        target.draw(hpStatDisplay, states);
        target.draw(powerStatDisplay, states);
        target.draw(*cardButton, states);
    }
}

void CardUI::OnDragMove(const sf::Vector2f &newPos)
{
	if (snapPoints.size() > 0)
	{
		auto closestSnapPoint = getClosestPoint<vector<sf::Vector2f>>(newPos, snapPoints, snapPointIndex);
		auto distance = getDistance(newPos, closestSnapPoint);
		if (distance < 25)
		{
			setPosition(closestSnapPoint);
			return;
		}
	}
	snapPointIndex = -1;
	setPosition(newPos);
}

void CardUI::OnDragStart()
{
	auto owningPlayer = owningCard->getOwner();
	setRotation(0);
	if (owningPlayer && owningPlayer->bIsMyTurn)
	{
		owningPlayer->battlefield->setDrawFreeSpaces(true, true);
		owningPlayer->battlefield->setDrawFreeSpaces(true, false);
		setSnapPoints(owningPlayer->battlefield->getFreeSnapPoints(true));
	}
	snapPointIndex = -1;
}

void CardUI::OnDragEnd()
{
	owningCard->playToIndex(snapPointIndex);
}


void CardUI::onCardClicked()
{
	if (! (owningCard && owningCard->getOwner())){
		cout << "CardUI: I need a card and a player!\n";
		throw;
	}
	auto owningPlayer = owningCard->getOwner();
	if (!owningPlayer->bIsMyTurn)
	{
		cout << "CardUI: Not my turn yet.\n";
		return;
	}
	if (owningCard->cardLocation == hand)
	{
		if (owningCard->canAfford())
		{
			owningCard->play();
		}
	}
	if (owningCard->cardLocation == battlefieldBattle || 
        owningCard->cardLocation == battlefieldBattort || 
        owningCard->cardLocation == battlefieldSupport)
	{
		if (owningPlayer->getSelectedCard() == owningCard)
		{
			owningPlayer->selectCard(nullptr);
			return;
		}
		owningPlayer->selectCard(owningCard);
	}
}

void CardUI::onCardBeginMouseover()
{
	preview = std::make_shared<CardPreview>(ui, owningCard);
	preview->setPosition({Settings::defaultWidth / 2, Settings::defaultHeight / 2});
	ui->addToHUDLayer(preview);
}

void CardUI::onCardEndMouseover()
{
	ui->removeFromHUDLayer(preview.get());
	preview.reset();
}

CardUI::~CardUI(){
    ui->removeFromHUDLayer(preview.get());
}