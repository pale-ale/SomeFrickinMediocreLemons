#include "UISystem.h"


bool UISystem::isCoordInBounds(sf::Vector2f coords, const UIElement& element) const{
    auto tl = element.GetPosition() - element.GetSize()/2.0f;
    auto br = element.GetBottomRight();
    return tl.x <= coords.x && tl.y <= coords.y &&
        br.x >= coords.x && br.y >= coords.y;
}

void UISystem::addListener(UIElement* newListener){
    for (UIElement* listener : eventListeners){
        if (listener == newListener){
            cout << "listener already added!\n";
            throw;
        }
    }
    eventListeners.push_back(newListener);
}

void UISystem::processEvents(vector<sf::Event> events){
    auto event_it = events.begin();
    while (event_it != events.end()){
        auto event = *event_it;
        if (event.type == sf::Event::MouseButtonPressed){
            auto eventListener_it = eventListeners.rbegin();
            while (eventListener_it != eventListeners.rend()){
                auto listener = *eventListener_it;
                auto mouseCoords = window->mapPixelToCoords(sf::Mouse::getPosition( *window));
                if (isCoordInBounds(mouseCoords, *listener)){
                    if (listener->isVisible && listener->OnMouseButtonDown()){
                        break; //i.e. the mouse event was handled, so no other object should be called again
                    };
                }
                eventListener_it++;
            }
        }
        event_it++;
    }
}

void UIElement::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    auto child_it = children.begin();
    while (child_it != children.end()){
        target.draw(**child_it);
        child_it++;
    }
};
