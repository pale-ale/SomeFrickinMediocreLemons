#include "PlayerHUD.h"
#include "../Card.h"

PlayerHUD::PlayerHUD(UISystem* ui):
UIElement(ui){
    deckCountText.setPosition(getPosition() );
    handCountText.setPosition(getPosition() + handTextOffset);
    cardActionShape.setPosition(getPosition() + cardActionShapeOffset);
    cardActionShape.setSize(cardActionShapeDimensions);
    cardActionShape.setFillColor({100,100,100,255});
    font->loadFromFile(Settings::validFontPath);
    deckCountText.setFont(*font);
    deckCountText.setString("0");
    handCountText.setFont(*font);
    handCountText.setString("0");
}

void PlayerHUD::generatePreview(const card* cardToPreview){
    if (cardPreview){
        removeChild(cardPreview.get());
        cardPreview = nullptr;
    }
    cardPreview = std::make_unique<CardPreview>(ui, cardToPreview);
    cardPreview->setPosition(getPosition() + cardPreviewOffset);
    addChild(cardPreview);
}

void PlayerHUD::removePreview(){
    if (cardPreview){
        removeChild(cardPreview.get());
        cardPreview = nullptr;
    }
}

void PlayerHUD::setPosition(const sf::Vector2f &newPosition)
{
    UIElement::setPosition(newPosition);
    deckCountText.setPosition(getPosition() + deckTextOffset);
    handCountText.setPosition(getPosition() + handTextOffset);
}

void PlayerHUD::setDeckCount(int deckCount){
    deckCountText.setString(std::to_string(deckCount));
}

void PlayerHUD::setHandCount(int handCount){
    handCountText.setString(std::to_string(handCount));
}
