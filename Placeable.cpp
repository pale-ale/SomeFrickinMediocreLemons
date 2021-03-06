#include "Placeable.h"
#include "Settings.h"

void Placeable::addChild(std::shared_ptr<Placeable> newChild){
    for (auto child : children){
        if (child == newChild){
            cout << "Placeable: Child already added!\n";
            throw;
        }
    }
    children.push_back(newChild);
}

void Placeable::reparent(Placeable *newParent){
    if (parent){
        parent->removeChild(this);
    }
    parent = newParent;
}

void Placeable::removeChild(Placeable *child){
    cout << name << ": Removing child \'" << child->name << "\' at " << child << ".\n";
    for (auto c : children){
        if (c.get() == child){
            child->parent = nullptr;
            children.remove(c);
            cout << name << ": Removed child \'" << child->name << "\' at " << child << ".\n";
            return;
        }
    }
    cout << name << ": Trying to remove child which is not a child or does not exist!\n";
    throw;
}

void Placeable::draw(sf::RenderTarget& target, sf::RenderStates state) const{
    for (auto child : children){
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

void Placeable::setPosition(const sf::Vector2f &newPosition){
    auto delta = newPosition - transform.getPosition();
    transform.setPosition(newPosition);
    for (auto &child : children){
        auto childPos = child->getPosition();
        child->setPosition(childPos + delta);
    }
}

void Placeable::setScale(float xScale, float yScale){
    transform.setScale({xScale, yScale});
}

void Placeable::setRotation(const float &newRotation){
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
    auto t = transform.getTransform();
    for (auto reverse_p = hitbox.rbegin(); reverse_p != hitbox.rend(); ++reverse_p){
        hb.push_back(t.transformPoint(*reverse_p));
    }
    return hb;
}
