#pragma once

#include <SFML/Graphics.hpp>
#include "../IAction.h"
#include "../ui/UIElement.h"

using std::shared_ptr;

class Button;
template <typename ...T>
class IEventCallback;

class ActionSelector : public UIElement{
    public: 
    ActionSelector(UISystem *ui);
    void addAction(IAction &action);
    void clear();

    private:
    vector<shared_ptr<Button>> actionButtons;
    vector<sf::Text> actionLabels;
    vector<shared_ptr<sf::Sprite>> actionSprites;
    sf::Vector2f firstElemOffset;
    sf::Vector2f offset;

    protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override{
        UIElement::draw(target, state);
        for (auto sprite : actionSprites){
            target.draw(*sprite);
        }
    }
};
