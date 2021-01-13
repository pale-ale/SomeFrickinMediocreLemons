#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class UIElement;

class UISystem : public sf::Drawable{
    public:
    UISystem(sf::RenderWindow* inWindow){window=inWindow;};
    void processEvents(vector<sf::Event> events);
    void addChild(UIElement* newChild);
    void removeChild(UIElement* child);
    const list<UIElement*>& getChildren(){return children;}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    private:
    list<UIElement*> children = {};
    sf::RenderWindow* window;
    bool isCoordInBounds(sf::Vector2f coords, const UIElement& element) const;
};

class UIElement : public sf::Drawable{
    public:
    virtual void OnMouseButtonDown(){}
    virtual void OnMouseButtonUp(){}
    virtual void SetPosition(sf::Vector2f);
    const sf::Vector2f GetPosition() const{return position;}
    bool isDragable;
    
    protected:
    sf::Vector2f position;
    sf::Vector2f size;

    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
    const sf::Vector2f getBottomRight() const{return position+size;}
};