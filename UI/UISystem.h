#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class UIElement : public sf::Drawable{
    public:
    void addChild(UIElement* newChild);
    void removeChild(UIElement* child);
    const list<UIElement*>& getChildren(){return children;}
    virtual bool OnMouseButtonDown(){return false;}
    virtual void OnMouseButtonUp(){}
    virtual void SetPosition(sf::Vector2f);
    virtual void SetRotation(float rotation);
    bool isDragable;
    bool isVisible = true;
    
    protected:
    sf::Vector2f position = {0,0};
    sf::Vector2f size = {0,0};
    float rotation = 0;
    list<UIElement*> children = {};

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
    const float GetRotation() const{return rotation;}
    const sf::Vector2f GetPosition() const{return position;}
    const sf::Vector2f GetSize() const{return size;}
    const sf::Vector2f GetBottomRight() const{return position+size/2.0f;}
    const sf::Vector2f Center() const{return position+sf::Vector2f({size.x/2, size.y/2});}
};

class UISystem : public UIElement{
    public:
    UISystem(sf::RenderWindow* inWindow){window=inWindow;};
    void processEvents(vector<sf::Event> events);
    list<UIElement*> eventListeners = {};
    void addListener(UIElement* newListener);
   
    private:
    sf::RenderWindow* window;
    bool isCoordInBounds(sf::Vector2f coords, const UIElement& element) const;
};