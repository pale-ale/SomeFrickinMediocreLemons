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

void Placeable::attachTo(Placeable* newParent){
    if (parent){
        parent->removeChild(this);
    }
    parent = newParent;
    parent->addChild(this);
}

void Placeable::removeChild(Placeable* child){
    //children.remove(child);
    cout << children.size() << endl;
}

void Placeable::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    auto child_it = children.begin();
    while (child_it != children.end()){
        target.draw(**child_it);
        child_it++;
    }
};

void Placeable::setPosition(sf::Vector2f newPosition){
    auto delta = newPosition - transform.getPosition();
    transform.setPosition(newPosition);
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto childPos = (**child_it).getPosition();
        (**child_it).setPosition(childPos + delta);
        child_it++;
    }
}

void Placeable::setRotation(float newRotation){
    auto delta = newRotation - transform.getRotation();
    transform.setRotation(newRotation);
    auto deltaTransform = sf::Transform().rotate(delta);
    auto child_it = children.begin();
    while (child_it != children.end()){
        auto childDelta = (*child_it)->getPosition() - getPosition();
        auto transformedChildDelta = deltaTransform.transformPoint(childDelta);
        (*child_it)->setPosition(getPosition() + transformedChildDelta);
        (*child_it)->setRotation(newRotation);
        child_it++;
    }
}
