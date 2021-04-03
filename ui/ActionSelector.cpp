#include "ActionSelector.h"

ActionSelector::ActionSelector(UISystem *ui) : UIElement(ui){
    firstElemOffset = sf::Vector2f{280, 105} + sf::Vector2f{12, 15}; //Playerhud rectangle + margin
    offset = {20, 0};
}

void ActionSelector::addAction(IAction &action){
    auto actionButton = make_shared<Button>(ui, sf::Color{255,100,100,100}, sf::Color{100,100,100,100}, 
                                                vector<sf::Vector2f>{{-10,-10}, {-10,10}, {10,10}, {10,-10}});
    actionButton->setPosition(firstElemOffset + (float)actionButtons.size() * offset);
    actionButton->initializeSubComponents();
    actionButton->onClickCallback = make_shared<EventCallback<IAction>>(&action, &IAction::triggerAction);
    actionButtons.push_back(actionButton);
    addChild(actionButton);

    auto actionSprite = make_shared<sf::Sprite>();
    actionSprite->setTexture(action.getActionImage());
    actionSprite->setScale({.5, .5});
    actionSprite->setOrigin({20,20});
    actionSprite->setPosition(firstElemOffset + (float)actionSprites.size() * offset);
    actionSprites.push_back(actionSprite);
}

void ActionSelector::clear(){
    children.clear();
    actionButtons.clear();
    actionSprites.clear();
}
