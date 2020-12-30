#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class UIElement;

class UISystem : public sf::Drawable{
    public:
    UISystem(sf::Window* inWindow){window=inWindow;};
    void processEvents(vector<sf::Event> events);
    void addChild(UIElement* newChild);
    void removeChild(UIElement* child);
    const list<UIElement*>& getChildren(){return children;}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    private:
    list<UIElement*> children = {};
    sf::Window* window;
    bool isCoordInBounds(sf::Vector2i coords, const UIElement& element) const;
};

class UIElement : public sf::Drawable{
    public:
    virtual void OnMouseButtonDown(sf::Event){};
    virtual void OnMouseButtonUp(sf::Event){};
    sf::Vector2f position;
    sf::Vector2f size;

    protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

    public:
    const sf::Vector2f getBottomRight() const{return position+size;}
};