#include "UISystem.h"

void Placeable::addChild(Placeable* newChild){
    for (Placeable* child : children){
        if (child == newChild){
            cout << "child already added!\n";
            throw;
        }
    }
    children.push_back(newChild);
}

void Placeable::SetPosition(sf::Vector2f newPosition){
    //transform.setPosition(newPosition);
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto posDelta = GetPosition() - (**child_it).GetPosition();
        (**child_it).SetPosition(newPosition + posDelta);
        child_it++;
    }
    position = newPosition;
}

void Placeable::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    auto child_it = children.begin();
    while (child_it != children.end()){
        target.draw(**child_it);
        child_it++;
    }
};

void Placeable::SetRotation(float rotation){
    float rotationDelta = rotation - this->rotation;
    this->rotation = rotation;
    auto t = sf::Transform().rotate(rotationDelta);
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto childpos = (**child_it).GetPosition();
        auto pos = t.transformPoint(childpos);
        (**child_it).SetPosition(pos);
        (**child_it).SetRotation((**child_it).GetRotation()+rotationDelta);
        child_it++;
    }
}
