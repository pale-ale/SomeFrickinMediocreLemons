#include "MultiSelect.h"

void MultiSelect::addOption(Option option){
    auto newButton = std::make_shared<Button>(ui, sf::Color{255,100,0,255}, sf::Color{200,75,0,255}, vector<sf::Vector2f>{});
    auto newLabel = std::make_shared<sf::Text>();
    auto labelPos = getPosition() + sf::Vector2f{-20, 0} + offset*(float)options.size();
    newLabel->setFont(labelFont);
    newLabel->setString(option.text);
    newLabel->setCharacterSize(10);
    if (options.size() % 2){
        newButton->setHitbox(buttonHitboxOdd);
        labelPos += sf::Vector2f{0, 12};
    }
    else{
        newButton->setHitbox(buttonHitboxEven);
        labelPos += sf::Vector2f{0, -25};
    }
    newLabel->setPosition(labelPos);
    newButton->setScale(2);
    newButton->initializeSubComponents();
    newButton->onClickCallback = option.callback;
    addChild(newButton);
    newButton->setPosition(getPosition() + offset*(float)options.size());
    options.push_back(option);
    optionLabels.push_back(newLabel);
    optionButtons.push_back(newButton);
}

void MultiSelect::clear(){
    children.clear();
    optionLabels.clear();
    optionButtons.clear();
}
