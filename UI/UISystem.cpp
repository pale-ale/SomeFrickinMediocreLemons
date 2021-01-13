#include "UISystem.h"


bool UISystem::isCoordInBounds(sf::Vector2f coords, const UIElement& element) const{
    auto tl = element.GetPosition();
    auto br = element.getBottomRight();
    return tl.x <= coords.x && tl.y <= coords.y &&
        br.x >= coords.x && br.y >= coords.y;
}

void UISystem::processEvents(vector<sf::Event> events){
    auto event_it = events.begin();
    while (event_it != events.end()){
        auto event = *event_it;
        if (event.type == sf::Event::MouseButtonPressed){
            auto child_it = children.begin();
            while (child_it != children.end()){
                auto child = *child_it;
                auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition( *window));
                if (isCoordInBounds(mouseCoords, *child)){
                    child->OnMouseButtonDown();
                }
                child_it++;
            }
        }
        event_it++;
    }
}

void UISystem::addChild(UIElement* newChild){
    children.push_back(newChild);
}

void UISystem::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    auto child_it = children.begin();
    while (child_it != children.end()){
        target.draw(**child_it);
        child_it++;
    }
}

void UIElement::SetPosition(sf::Vector2f newPosition){
    position = newPosition;
}

void UIElement::draw(sf::RenderTarget& target, sf::RenderStates state) const{};