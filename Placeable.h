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
    virtual void SetPosition(sf::Vector2f);
    virtual void SetRotation(float rotation);
      
    protected:
    sf::Transformable transform;
    sf::Vector2f position = {0,0};
    sf::Vector2f size = {0,0};
    float rotation = 0;
    list<Placeable*> children = {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
    const float GetRotation() const{return rotation;}
    const sf::Vector2f GetPosition() const{return position;}
    const sf::Vector2f GetSize() const{return size;}
    const sf::Vector2f GetBottomRight() const{return position+size/2.0f;}
    const sf::Vector2f Center() const{return position+sf::Vector2f({size.x/2, size.y/2});}
};
