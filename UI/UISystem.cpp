#include "UISystem.h"

bool UISystem::isCoordInBounds(sf::Vector2f coords, const UIElement& element) const{
    auto tl = element.position;
    auto br = element.getBottomRight();
    return tl.x <= coords.x && tl.y <= coords.y &&
        br.x >= coords.x && br.y >= coords.y;
}

void UISystem::processUIEvents(vector<sf::Event> events){
    auto event_it = events.begin();
    while (event_it != events.end()){
        auto event = *event_it;
        if (event.type == sf::Event::MouseButtonPressed){
            auto child_it = children->begin();
            while (child_it != children->end()){
                auto child = *child_it;
                auto mouseCoords = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                if (isCoordInBounds(mouseCoords, *child)){
                    child->OnMouseButtonDown();
                }
                child_it++;
            }
        }
        event_it++;
    }
}