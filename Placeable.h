#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Placeable : public sf::Drawable{
    public:
    void addChild(Placeable* newChild);
    void removeChild(Placeable* child);
    const list<Placeable*>& getChildren(){return children;}
    virtual void setPosition(sf::Vector2f);
    virtual void setRotation(float rotation);
    void attachTo(Placeable* newParent);
    void detach();
    
    protected:
    sf::Transformable transform;
    Placeable* parent = nullptr;
    sf::Vector2f size = {0,0};
    list<Placeable*> children = list<Placeable*>();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
    const float getRotation() const{return transform.getRotation();}
    const sf::Vector2f getPosition() const{return transform.getPosition();}
    const sf::Vector2f getSize() const{return size;}
    const sf::Vector2f getBottomRight() const{return getPosition() + size/2.0f;}
    const sf::Vector2f center() const{return getPosition() + sf::Vector2f({size.x/2, size.y/2});}
};
