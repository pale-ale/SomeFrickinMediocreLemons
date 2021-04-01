#include "MultiSelect.h"

void MultiSelect::addOption(Option option){
    auto newButton = std::make_shared<Button>(ui, vector<sf::Vector2f>{}, sf::Color{255,100,0,255});
    if (options.size() % 2){
        newButton->setHitbox(buttonHitboxOdd);
    }
    else{
        newButton->setHitbox(buttonHitboxEven);
    }
    newButton->setScale(2);
    newButton->initializeSubComponents();
    addChild(newButton);
    newButton->setPosition(getPosition() + offset*(float)options.size());
    options.push_back(option);
}
