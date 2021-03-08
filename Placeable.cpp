#include "Placeable.h"
#include "../Settings.h"

void Placeable::addChild(Placeable* newChild){
    for (Placeable* child : children){
        if (child == newChild){
            cout << "child already added!\n";
            throw;
        }
    }
    children.push_back(newChild);
    newChild->parent = this;
}

void Placeable::attachTo(Placeable* newParent){
    if (parent){
        parent->removeChild(this);
    }
    parent = newParent;
    parent->addChild(this);
}

void Placeable::setSize(const sf::Vector2f& newSize){
    auto s = newSize * 0.5f;
    hitbox.erase(hitbox.begin(), hitbox.end());
    hitbox.push_back(-s);
    hitbox.push_back({-s.x, s.y});
    hitbox.push_back(s);
    hitbox.push_back({s.x, -s.y});
    size = newSize;
}

void Placeable::removeChild(Placeable* child){
    children.remove(child);
}

void Placeable::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    for (auto& child : children){
        target.draw(*child);
    }
    if (Settings::bDrawDebugHitbox){
        sf::ConvexShape shape;
        shape.setPointCount(hitbox.size());
        shape.setFillColor({0, 100, 100, 100});
        auto& hb = getHitboxPolygonGlobal();
        for (int i = 0; i < hitbox.size(); i++)
        {
            shape.setPoint(i, hb[i]);
        }
        target.draw(shape);
    }
};

void Placeable::setPosition(sf::Vector2f newPosition){
    auto delta = newPosition - transform.getPosition();
    transform.setPosition(newPosition);
    for (auto& child : children){
        auto childPos = child->getPosition();
        child->setPosition(childPos + delta);
    }
}

void Placeable::setRotation(float newRotation){
    auto delta = newRotation - transform.getRotation();
    transform.setRotation(newRotation);
    auto deltaTransform = sf::Transform().rotate(delta);
    for (auto& child : children){
        auto childDelta = child->getPosition() - getPosition();
        auto transformedChildDelta = deltaTransform.transformPoint(childDelta);
        child->setPosition(getPosition() + transformedChildDelta);
        child->setRotation(child->getRotation() + delta);
    }
}

const vector<sf::Vector2f> Placeable::getHitboxPolygonGlobal() const{
    vector<sf::Vector2f> hb;
    for (auto reverse_p = hitbox.rbegin(); reverse_p != hitbox.rend(); ++reverse_p){
        hb.push_back(transform.getTransform().transformPoint(*reverse_p));
    }
    return hb;
}
