#include "MultiSelect.h"

void MultiSelect::addOption(Option option){
    auto newButton = std::make_shared<Button>(ui, vector<sf::Vector2f>{}, sf::Color{100,100,0});
    if (options.size() % 2){
        newButton->setHitbox(buttonHitboxOdd);
    }
    else{
        newButton->setHitbox(buttonHitboxEven);
    }
    addChild(newButton);
    newButton->setPosition(getPosition());
    newButton->initializeSubComponents();
}
