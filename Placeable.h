#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::list;

class UISystem;

class Placeable : public sf::Drawable, public std::enable_shared_from_this<Placeable>
{
public:
    Placeable(){}
    void addChild(std::shared_ptr<Placeable> newChild);
    void reparent(Placeable *newParent);
    virtual void removeChild(Placeable *child);
    list<std::shared_ptr<Placeable>> getChildren() const { return children; }
    virtual void setPosition(const sf::Vector2f &newPosition);
    virtual void setRotation(const float &rotation);
    virtual void setScale(float xScale, float yScale);
    virtual void setScale(int scale){setScale(scale, scale);}
    virtual void setHitbox(const vector<sf::Vector2f> &newHitbox){hitbox = newHitbox;}
    virtual void initializeSubComponents(){};
    void setChildren(list<std::shared_ptr<Placeable>> newChildren) { children = newChildren; };
    virtual const string &getName() const {return name;}
    void setName(const string &newName){name = newName;}

protected:
    sf::Transformable transform;
    Placeable *parent = nullptr;
    string name = "Placeable";
    UISystem *ui = nullptr;
    vector<sf::Vector2f> hitbox;
    sf::Vector2f size = {0, 0};
    list<std::shared_ptr<Placeable>> children;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

public:
    const float getRotation() const { return transform.getRotation(); }
    const sf::Vector2f getPosition() const { return transform.getPosition(); }
    const sf::Vector2f getBottomRight() const { return getPosition() + size / 2.0f; }
    const vector<sf::Vector2f> getHitboxPolygonGlobal() const;
    const sf::Vector2f center() const { return getPosition() + sf::Vector2f({size.x / 2, size.y / 2}); }
};
