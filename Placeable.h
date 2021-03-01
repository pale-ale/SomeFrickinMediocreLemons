#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class UIElement;
class UISystem;

class Placeable : public sf::Drawable
{
public:
    Placeable(){}
    void addChild(Placeable *newChild);
    void removeChild(Placeable *child);
    const list<Placeable *> &getChildren() { return children; }
    virtual void setPosition(sf::Vector2f);
    virtual void setRotation(float rotation);
    void setSize(const sf::Vector2f& newSize);
    void attachTo(Placeable *newParent);
    void detach();
    void setChildren(list<Placeable *> newChildren) { children = newChildren; };

protected:
    sf::Transformable transform;
    Placeable *parent = nullptr;
    UISystem *ui = nullptr;
    vector<sf::Vector2f> hitbox;
    sf::Vector2f size = {0, 0};
    list<Placeable *> children = list<Placeable *>();
    void updateHitbox();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

public:
    const float getRotation() const { return transform.getRotation(); }
    const sf::Vector2f getPosition() const { return transform.getPosition(); }
    const sf::Vector2f getSize() const { return size; }
    const sf::Vector2f getBottomRight() const { return getPosition() + size / 2.0f; }
    const vector<sf::Vector2f> getHitboxPolygonGlobal() const;
    const sf::Vector2f center() const { return getPosition() + sf::Vector2f({size.x / 2, size.y / 2}); }
};
