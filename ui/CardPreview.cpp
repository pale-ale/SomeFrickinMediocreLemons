#include "CardPreview.h"
#include "../IAction.h"

CardPreview::CardPreview(UISystem* ui, const Card* cardToPreview): UIElement(ui),
description{std::make_shared<TextBox>(ui)}
{
    font.loadFromFile(Settings::validFontPath);
    cardTitle.setFont(font);
    cardTitle.setString(cardToPreview->getName());
    cardTitle.setOrigin({cardTitle.getLocalBounds().width/2, cardTitle.getLocalBounds().height/2});
    string cardDescription = cardToPreview->getDescription() + "\n";
    for (auto action : cardToPreview->getActions()){
        cardDescription.append(action->getActionString() + "\n");
    }
    addChild(description);
    description->changeContent(cardDescription);
    description->setPosition(this->getPosition());
    description->setScale(.25f,.25f);
    description->changeSize(this->size);
    background.setFillColor({30,0,0,200});
    background.setSize(size);
    background.setOrigin(size/2.0f);
    cardImage.setTexture(*(cardToPreview->getTexture()), true);
    cardImage.setScale(sf::Vector2f{0.0335f, 0.0335f}*2.5f);
    cardImage.setOrigin({cardImage.getLocalBounds().width/2, cardImage.getLocalBounds().height/2});
    FMana cardCost = cardToPreview->cost;
    costDisplayRed.setFillColor(Settings::redColor);
    costDisplayRed.setString(to_string(cardCost.Red));
    costDisplayRed.setFont(font);
    costDisplayRed.setScale(0.5, 0.5);
    costDisplayGreen.setFillColor(Settings::greenColor);
    costDisplayGreen.setString(to_string(cardCost.Green));
    costDisplayGreen.setFont(font);
    costDisplayGreen.setScale(0.5, 0.5);
    costDisplayBlue.setFillColor(Settings::blueColor);
    costDisplayBlue.setString(to_string(cardCost.Blue));
    costDisplayBlue.setFont(font);
    costDisplayBlue.setScale(0.5, 0.5);
    costDisplayBlack.setFillColor(Settings::blackColor);
    costDisplayBlack.setString(to_string(cardCost.Black));
    costDisplayBlack.setFont(font);
    costDisplayBlack.setScale(0.5, 0.5);
    costDisplayWhite.setFillColor(Settings::whiteColor);
    costDisplayWhite.setString(to_string(cardCost.White));
    costDisplayWhite.setFont(font);
    costDisplayWhite.setScale(0.5, 0.5);
}
