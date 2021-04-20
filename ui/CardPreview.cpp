#include "CardPreview.h"

CardPreview::CardPreview(UISystem* ui, const Card* cardToPreview): UIElement(ui)
{
    font.loadFromFile(Settings::validFontPath);
    cardTitle.setFont(font);
    description.setFont(font);
    cardTitle.setString(cardToPreview->getName());
    description.setString(cardToPreview->getDescription());
    //description.setCharacterSize(10);
    description.setScale(.2,.2);
    cardTitle.setOrigin({cardTitle.getLocalBounds().width/2, cardTitle.getLocalBounds().height/2});
    description.setOrigin({description.getLocalBounds().width/2, description.getLocalBounds().height/2});
    background.setFillColor({50,50,50,100});
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
