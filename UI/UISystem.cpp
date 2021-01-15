#include "UISystem.h"


bool UISystem::isCoordInBounds(sf::Vector2f coords, const UIElement& element) const{
    auto tl = element.GetPosition();
    auto br = element.GetBottomRight();
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

void UIElement::addChild(UIElement* newChild){
    for (UIElement* child : children){
        if (child == newChild){
            cout << "child already added!\n";
            throw;
        }
    }
    children.push_back(newChild);
}

void UIElement::SetPosition(sf::Vector2f newPosition){
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto posDelta = GetPosition() - (**child_it).GetPosition();
        (**child_it).SetPosition(newPosition + posDelta);
        child_it++;
    }
    position = newPosition;
}

void UIElement::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    auto child_it = children.begin();
    while (child_it != children.end()){
        target.draw(**child_it);
        child_it++;
    }
};

void UIElement::SetRotation(float rotation){
    float rotationDelta = rotation - this->rotation;
    this->rotation = rotation;
    auto t = sf::Transform(1,0,0,0,1,0,0,0,1).rotate(rotationDelta);
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto childpos = (**child_it).GetPosition();
        auto pos = t.transformPoint(childpos);
        (**child_it).SetPosition(pos);
        (**child_it).SetRotation((**child_it).GetRotation()+rotationDelta);
        child_it++;
    }
}
