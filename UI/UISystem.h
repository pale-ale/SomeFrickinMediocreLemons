#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include "../Placeable.h"

using namespace std;

class UIElement : public Placeable{
    public:
    virtual bool OnMouseButtonDown(){return false;}
    virtual void OnMouseButtonUp(){}
    bool isDragable;
    bool isVisible = true;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
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